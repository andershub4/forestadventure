/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Configuration.h"
#include "Entity/EntityTextures.h"
#include "Folder.h"
#include "Logging.h"
#include "Resource/TextureManager.h"
#include "Tile/TileMapReader.h"

namespace FA {

Level::Level(MessageBus &messageBus, sf::RenderTarget &renderTarget, TextureManager &textureManager)
    : textureManager_(textureManager)
    , animationManager_(textureManager)
    , tileMap_(textureManager, scale_)
    , renderTarget_(renderTarget)
    , camera_(renderTarget_.getSize())
    , entityManager_(messageBus, animationManager_)
{}

Level::~Level() = default;

void Level::Load(const std::string &mapPath)
{
    LOG_INFO_ENTER_FUNC();

    auto ssPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/spritesheets/";
    for (auto &v : Entity::textures) {
        auto p = ssPath + v.path_;
        textureManager_.Add(v.name_, p);
    }

    LOG_INFO("Register animation DBs");
    animationManager_.RegisterDBs();

    LOG_INFO("Create tile map");
    Tile::TileMapReader tileMapReader;
    auto tileMapData = tileMapReader.Parse(mapPath);
    tileMap_.Create(tileMapData);

    LOG_INFO("Create entities");
    for (const auto &objectData : tileMap_.GetObjectGroup("Object Layer 1")) {
        Entity::Configuration configuration;
        configuration.entityType_ = objectData.type_;
        configuration.position_ = static_cast<sf::Vector2f>(objectData.position_);
        configuration.faceDir_ = objectData.faceDir_;
        configuration.velocity_ = 120.0;
        configuration.scale_ = static_cast<float>(scale_);
        auto entity = entityManager_.Create(configuration);
        if (configuration.entityType_ == EntityType::Player) {
            camera_.Follow(entity);
        }
    }

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
    entityManager_.LateUpdate();
    camera_.UpdatePosition(renderTarget_, tileMap_.GetSize());
}

void Level::Draw()
{
    renderTarget_.draw(backgroundSprite_);
    entityManager_.DrawTo(renderTarget_);
    for (const auto &tile : fringeLayer_) {
        renderTarget_.draw(tile);
    }
}

void Level::EnableInput(bool enable)
{
    entityManager_.EnableInput(enable);
}

}  // namespace FA
