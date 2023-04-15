/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Camera.h"
#include "EntityManager.h"
#include "Folder.h"
#include "LevelCreator.h"
#include "Logging.h"
#include "MapData.h"
#include "Sheets.h"
#include "TileMap.h"

namespace FA {

namespace World {

Level::Level(Shared::MessageBus &messageBus, Shared::TextureManager &textureManager, const sf::Vector2u &viewSize)
    : sheetManager_(textureManager)
    , tileMap_(std::make_unique<TileMap>(sheetManager_))
    , viewSize_(viewSize)
    , entityManager_(std::make_unique<Entity::EntityManager>(messageBus, sheetManager_, cameraManager_))
    , levelCreator_(std::make_unique<LevelCreator>())
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
    cameraManager_.CreateCamera(viewSize_, tileMap_->GetSize());  // Entities need camera, create before
    CreateEntities();
    LOG_INFO_EXIT_FUNC();
}

sf::View Level::GetView()
{
    auto &camera = cameraManager_.GetCamera();
    return camera.GetView();
}

void Level::Update(float deltaTime)
{
    entityManager_->HandleCreatedEntities();
    cameraManager_.Update(deltaTime);
    entityManager_->Update(deltaTime);
    entityManager_->HandleDeletedEntities();
}

void Level::Draw(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(backgroundSprite_);
    entityManager_->DrawTo(renderTarget);
    for (const auto &tile : fringeLayer_) {
        renderTarget.draw(tile);
    }
}

void Level::LoadEntitySheets()
{
    auto sheetPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/";
    for (const auto &sheetData : textureSheets) {
        sheetManager_.LoadSheet(sheetPath, sheetData);
    }
}

void Level::LoadTileMap(const std::string &levelName)
{
    auto path = GetAssetsPath() + "/map/" + levelName;
    tileMap_->Load(path);
    tileMap_->Setup();
}

void Level::CreateMap()
{
    LOG_INFO("Create map");
    levelCreator_->AddBackground(tileMap_->GetLayer("Ground Layer 1"));
    levelCreator_->AddBackground(tileMap_->GetLayer("Ground Layer 2"));
    levelCreator_->CreateBackground(tileMap_->GetSize(), backgroundTexture_);
    backgroundTexture_.display();
    backgroundSprite_.setTexture(backgroundTexture_.getTexture());
    fringeLayer_ = levelCreator_->CreateFringe(tileMap_->GetLayer("Fringe Layer"));
}

void Level::CreateEntities()
{
    LOG_INFO("Create entities");
    Shared::MapData mapData{tileMap_->GetSize()};
    for (const auto &data : tileMap_->GetObjectGroup("Object Layer 1")) {
        entityManager_->CreateEntity(data.typeStr_, data.position_, data.properties_, mapData);
    }
    for (const auto &data : tileMap_->GetLayer("Dynamic Layer 1")) {
        entityManager_->CreateTileEntity(data.position_, data.graphic_, mapData);
    }
    entityManager_->HandleCreatedEntities();
}

}  // namespace World

}  // namespace FA
