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

Level::Level(MessageBus &messageBus, TextureManager &textureManager)
    : animationManager_(textureManager)
    , tileSet_(textureManager)
    , entitySystem_(messageBus)
    , tileMap_(tileSet_)
    , tmxParser_("assets/map/test.tmx")
{}

Level::~Level() = default;

void Level::Update(float deltaTime)
{
    entitySystem_.Update(deltaTime);
}

void Level::DrawTo(sf::RenderTarget &renderTarget)
{
    tileMap_.DrawTo(renderTarget);
    entitySystem_.DrawTo(renderTarget);
}

void Level::Create(Camera &camera)
{
    animationManager_.RegisterFactories();

    std::vector<Entity::Configuration> configurations = {
        {EntityType::Player, {8 * 56 * 2, 8 * 56}, FaceDirection::Down, 120.0, TileType::None},
        {EntityType::Mole, {8 * 32, 8 * 32}, FaceDirection::Right, 120.0, TileType::None},
        {EntityType::Static, {8 * 64, 8 * 10}, FaceDirection::Down, 0.0, TileType::Stone},
        {EntityType::Static, {8 * 68, 8 * 10}, FaceDirection::Down, 0.0, TileType::Stone},
        {EntityType::Static, {8 * 64, 8 * 14}, FaceDirection::Down, 0.0, TileType::Stone},
        {EntityType::Static, {8 * 68, 8 * 14}, FaceDirection::Down, 0.0, TileType::Stone}};

    for (const auto &configuration : configurations) {
        entitySystem_.Create(animationManager_, tileSet_, camera, configuration);
    }

    tileMap_.Load();
    tmxParser_.Load();
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
