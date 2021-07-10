/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Camera.h"
#include "Entity/Configuration.h"
#include "Logging.h"
#include "Misc/TextureManager.h"

namespace FA {

Level::Level(const Tile::TileMapData &tileMapData, TextureManager &textureManager)
    : animationManager_(textureManager)
    , tileMap_(tileMapData, textureManager, scale_)
{}

Level::~Level() = default;

void Level::Update(float deltaTime)
{
    entityManager_.Update(deltaTime);
    entityManager_.LateUpdate();
}

void Level::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(backgroundSprite_);
    entityManager_.DrawTo(renderTarget);
    for (const auto &tile : fringeLayer_) {
        renderTarget.draw(tile);
    }
}

void Level::Create(Camera &camera, MessageBus &messageBus)
{
    LOG_INFO_ENTER_FUNC();
    LOG_INFO("Register animation DBs");
    animationManager_.RegisterDBs();

    LOG_INFO("Create tile map");
    tileMap_.Create();

    LOG_INFO("Create entities");
    for (const auto &objectData : tileMap_.GetObjectGroup("Object Layer 1")) {
        auto type = objectData.type_;
        auto entity = factory_.Create(type, messageBus);
        Entity::Configuration configuration;
        configuration.position_ = static_cast<sf::Vector2f>(objectData.position_);
        configuration.faceDir_ = objectData.faceDir_;
        configuration.velocity_ = 120.0;
        configuration.scale_ = static_cast<float>(scale_);
        entity->OnCreate(animationManager_, camera, configuration);
        entityManager_.AddEntity(std::move(entity));
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

void Level::EnableInput(bool enable)
{
    entityManager_.EnableInput(enable);
}

sf::Vector2u Level::GetSize() const
{
    return tileMap_.GetSize();
}

}  // namespace FA
