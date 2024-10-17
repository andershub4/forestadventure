/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include "CameraView.h"
#include "EntityManager.h"
#include "Folder.h"
#include "LevelCreator.h"
#include "Logging.h"
#include "RenderTargetIf.h"
#include "Resource/ResourceId.h"
#include "Resource/SpriteSheet.h"
#include "Sheets.h"
#include "TileMap.h"
#include "View.h"

namespace FA {

namespace World {

Level::Level(Shared::MessageBus &messageBus, Shared::TextureManager &textureManager, const sf::Vector2u &viewSize)
    : textureManager_(textureManager)
    , sheetManager_()
    , tileMap_(std::make_unique<TileMap>(textureManager, sheetManager_))
    , viewSize_(viewSize)
    , entityManager_(std::make_unique<Entity::EntityManager>(messageBus, textureManager, sheetManager_, cameraViews_))
    , levelCreator_(std::make_unique<LevelCreator>(textureManager, sheetManager_))
{}

Level::~Level() = default;

void Level::Load(const std::string &levelName)
{
    LoadTileMap(levelName);
    LoadEntitySheets();
}

void Level::Create()
{
    LOG_INFO_ENTER_FUNC();
    CreateMap();
    cameraViews_.CreateCameraView(viewSize_, tileMap_->GetSize(),
                                  zoomFactor_);  // Entities need cameraView, create before
    CreateEntities();
    LOG_INFO_EXIT_FUNC();
}

Graphic::View Level::GetView() const
{
    auto &cameraView = cameraViews_.GetCameraView();
    Graphic::View view;
    view.setSize(static_cast<sf::Vector2f>(viewSize_));
    view.zoom(zoomFactor_);
    view.setCenter(cameraView.GetPosition());

    return view;
}

void Level::Update(float deltaTime)
{
    entityManager_->HandleCreationQueue();
    cameraViews_.Update(deltaTime);
    for (auto &animation : animationLayer_) {
        animation.Update(deltaTime);
    }
    entityManager_->Update(deltaTime);
    entityManager_->DetectCollisions();
    entityManager_->DetectOutsideTileMap(tileMap_->GetSize());
    entityManager_->HandleCollisions();
    entityManager_->HandleOutsideTileMap();
    entityManager_->HandleDeletionQueue();
}

void Level::Draw(Graphic::RenderTargetIf &renderTarget)
{
    renderTarget.draw(backgroundSprite_);
    entityManager_->DrawTo(renderTarget);
    for (const auto &tile : fringeLayer_) {
        renderTarget.draw(tile);
    }
    for (const auto &animation : animationLayer_) {
        animation.DrawTo(renderTarget);
    }
}

void Level::LoadEntitySheets()
{
    auto sheetPath = Util::GetAssetsPath() + "/tiny-RPG-forest-files/PNG/";
    for (const auto &sheetData : textureSheets) {
        auto path = sheetPath + sheetData.path_;
        Shared::ResourceId id = textureManager_.Load(path);
        sf::Vector2u textureSize = textureManager_.Get(id)->getSize();
        auto sheet = std::make_unique<Shared::SpriteSheet>(id, textureSize, sheetData.rectCount_);
        sheetManager_.AddSheet(sheetData.name_, std::move(sheet));
    }
}

void Level::LoadTileMap(const std::string &levelName)
{
    auto path = Util::GetAssetsPath() + "/map/" + levelName;
    tileMap_->Load(path);
    tileMap_->Setup();
}

void Level::CreateMap()
{
    LOG_INFO("Create map");
    levelCreator_->AddBackground(tileMap_->GetLayer("Ground Layer 1"));
    levelCreator_->AddBackground(tileMap_->GetLayer("Ground Layer 2"));
    auto size = tileMap_->GetSize();
    backgroundTexture_.create(size.x, size.y);
    levelCreator_->CreateBackground(backgroundTexture_);
    backgroundTexture_.display();
    backgroundSprite_.setTexture(backgroundTexture_.getTexture());
    fringeLayer_ = levelCreator_->CreateFringe(tileMap_->GetLayer("Fringe Layer"));
    animationLayer_ = levelCreator_->CreateAnimations(tileMap_->GetLayer("Dynamic Layer 1"));
}

void Level::CreateEntities()
{
    LOG_INFO("Create entities");
    for (const auto &data : tileMap_->GetObjectGroup("Object Layer 1")) {
        entityManager_->AddToCreationQueue(data.typeStr_, data.position_, data.size_, data.properties_);
    }
    for (const auto &data : tileMap_->GetObjectGroup("Collision Layer 1")) {
        entityManager_->AddToCreationQueue(data.typeStr_, data.position_, data.size_, data.properties_);
    }

    entityManager_->HandleCreationQueue();
}

}  // namespace World

}  // namespace FA
