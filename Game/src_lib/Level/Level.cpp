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

Level::Level(MessageBus &messageBus, const Tile::TileMapData &tileMapData, TextureManager &textureManager)
    : animationManager_(textureManager)
    , entitySystem_(messageBus)
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

void Level::Create(Camera &camera)
{
    animationManager_.RegisterFactories();

    std::vector<Entity::Configuration> configurations = {
        {EntityType::Player, {8 * 56 * 2, 8 * 56}, FaceDirection::Down, 120.0, TileType::None},
        {EntityType::Mole, {8 * 32, 8 * 32}, FaceDirection::Right, 120.0, TileType::None}};

    for (const auto &configuration : configurations) {
        entitySystem_.Create(animationManager_, camera, configuration);
    }

    tileMap_.Create();

    backgroundTexture_.create(tileMap_.GetSize().x, tileMap_.GetSize().y);
    for (const auto &tile : tileMap_.GetLayer(3)) {
        backgroundTexture_.draw(tile);
    }
    for (const auto &tile : tileMap_.GetLayer(4)) {
        backgroundTexture_.draw(tile);
    }
    backgroundTexture_.display();
    backgroundSprite_.setTexture(backgroundTexture_.getTexture());

    fringeLayer_ = tileMap_.GetLayer(5);
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
