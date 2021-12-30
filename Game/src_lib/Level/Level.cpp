/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/PropertyData.h"
#include "Logging.h"
#include "Tile/TileMapReader.h"
#include "Folder.h"

namespace FA {

Level::Level(MessageBus &messageBus, TextureManager &textureManager)
    : factory_(messageBus)
    , entityManager_(factory_)
    , textureManager_(textureManager)
    , tileMap_(textureManager, scale_)
{}

Level::~Level() = default;

void Level::Load()
{
    auto path = GetAssetsPath() + "/map/test.tmx";
    Tile::TileMapReader tileMapReader;
    auto tileMapData = tileMapReader.Parse(path);
    tileMap_.Create(tileMapData);
}

void Level::Create(CameraManager &cameraManager)
{
    LOG_INFO_ENTER_FUNC();

    LOG_INFO("Create entities");
    for (const auto &objectData : tileMap_.GetObjectGroup("Object Layer 1")) {
        Entity::PropertyData data;
        data.position_ = static_cast<sf::Vector2f>(objectData.position_);
        data.faceDir_ = objectData.faceDir_;
        data.velocity_ = 120.0;
        data.scale_ = static_cast<float>(tileMap_.GetScale());
        entityManager_.Create(objectData.type_, data, cameraManager, textureManager_);
    }

    entityManager_.Init();

    LOG_INFO("Create background texture");
    backgroundTexture_.create(tileMap_.GetSize().x, tileMap_.GetSize().y);
    for (const auto &tile : tileMap_.GetLayer("Ground Layer 1")) {
        backgroundTexture_.draw(tile);
    }
    for (const auto &tile : tileMap_.GetLayer("Ground Layer 2")) {
        backgroundTexture_.draw(tile);
    }
    backgroundTexture_.display();
    backgroundSprite_.setTexture(backgroundTexture_.getTexture());

    fringeLayer_ = tileMap_.GetLayer("Fringe Layer");
    LOG_INFO_EXIT_FUNC();
}

void Level::Update(float deltaTime)
{
    entityManager_.Update(deltaTime);
}

void Level::Draw(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(backgroundSprite_);
    entityManager_.DrawTo(renderTarget);
    for (const auto &tile : fringeLayer_) {
        renderTarget.draw(tile);
    }
}

void Level::EnableInput(bool enable)
{
    entityManager_.EnableInput(enable);
}

sf::Vector2u Level::GetMapSize() const
{
    return tileMap_.GetSize();
}

}  // namespace FA
