/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include "CameraView.h"
#include "CollisionHandler.h"
#include "DrawHandler.h"
#include "EntityDb.h"
#include "EntityHandler.h"
#include "EntityIf.h"
#include "EntityLifePool.h"
#include "Factory.h"
#include "Folder.h"
#include "Id.h"
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
    : messageBus_(messageBus)
    , textureManager_(textureManager)
    , sheetManager_()
    , tileMap_(std::make_unique<TileMap>(textureManager, sheetManager_))
    , viewSize_(viewSize)
    , factory_(std::make_unique<Entity::Factory>())
    , entityDb_(std::make_unique<Entity::EntityDb>())
    , collisionHandler_(std::make_unique<Entity::CollisionHandler>(*entityDb_))
    , drawHandler_(std::make_unique<Entity::DrawHandler>(*entityDb_))
    , entityLifePool_(std::make_unique<Entity::EntityLifePool>())
    , entityHandler_(std::make_unique<Entity::EntityHandler>(*entityDb_))
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
    HandleCreationPool();
    cameraViews_.Update(deltaTime);
    for (auto &animation : animationLayer_) {
        animation.Update(deltaTime);
    }
    entityHandler_->Update(deltaTime);
    collisionHandler_->DetectCollisions();
    collisionHandler_->DetectOutsideTileMap(tileMap_->GetSize());
    collisionHandler_->HandleCollisions();
    collisionHandler_->HandleOutsideTileMap();
    HandleDeletionPool();
}

void Level::Draw(Graphic::RenderTargetIf &renderTarget)
{
    renderTarget.draw(backgroundSprite_);
    drawHandler_->DrawTo(renderTarget);
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
    for (const auto &data : tileMap_->GetEntityGroup("Object Layer 1")) {
        entityLifePool_->AddToCreationPool(data);
    }
    for (const auto &data : tileMap_->GetEntityGroup("Collision Layer 1")) {
        entityLifePool_->AddToCreationPool(data);
    }
    HandleCreationPool();
}

void Level::HandleCreationPool()
{
    auto creationPool = entityLifePool_->MoveCreationPool();
    for (const auto &data : creationPool) {
        auto id = entityHandler_->AddEntity(data, *factory_, messageBus_, textureManager_, sheetManager_, cameraViews_,
                                            *entityLifePool_);
        drawHandler_->AddDrawable(id);
        collisionHandler_->AddCollider(id);
    }
}

void Level::HandleDeletionPool()
{
    auto deletionPool = entityLifePool_->MoveDeletionPool();
    for (const auto &id : deletionPool) {
        drawHandler_->RemoveDrawable(id);
        collisionHandler_->RemoveCollider(id);
        entityHandler_->RemoveEntity(id);
    }
}

}  // namespace World

}  // namespace FA
