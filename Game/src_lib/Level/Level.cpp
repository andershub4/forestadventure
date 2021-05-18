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
#include "Misc/TextureManager.h"

namespace FA {

Level::Level(const Tile::TileMapData &tileMapData, TextureManager &textureManager)
    : animationManager_(textureManager)
    , tileMap_(tileMapData)
{}

Level::~Level() = default;

void Level::Update(float deltaTime)
{
    entitySystem_.Update(deltaTime);
}

void Level::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(backgroundSprite_);
    entitySystem_.DrawTo(renderTarget);
    for (const auto &tile : fringeLayer_) {
        renderTarget.draw(tile);
    }
}

void Level::Create(Camera &camera, MessageBus &messageBus)
{
    animationManager_.RegisterFactories();

    std::vector<Entity::Configuration> configurations = {
        {EntityType::Player, {8 * 56 * 2, 8 * 56}, FaceDirection::Down, 120.0, TileType::None},
        {EntityType::Mole, {8 * 32, 8 * 32}, FaceDirection::Right, 120.0, TileType::None}};

    Entity::EntityId id = 0;
    for (const auto &configuration : configurations) {
        auto type = configuration.entityType_;
        auto entity = factory_.Create(type, id, messageBus);
        entity->OnCreate(animationManager_, camera, configuration);
        entitySystem_.AddEntity(id, std::move(entity));
        id++;
    }

    tileMap_.Create();

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
}

void Level::EnableInput(bool enable)
{
    entitySystem_.EnableInput(enable);
}

sf::Vector2u Level::GetSize() const
{
    return tileMap_.GetSize();
}

}  // namespace FA
