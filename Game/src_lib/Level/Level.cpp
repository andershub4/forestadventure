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
    , entitySystem_(messageBus)
    , tileMapReader_("assets/map/test.tmx")
    , textureManager_(textureManager)
{}

Level::~Level() = default;

void Level::Update(float deltaTime)
{
    entitySystem_.Update(deltaTime);
}

void Level::DrawTo(sf::RenderTarget &renderTarget)
{
    tileMap_->DrawTo(renderTarget);
    entitySystem_.DrawTo(renderTarget);
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

    tileMapReader_.Load(textureManager_);
    auto tileMapData = tileMapReader_.GetTileMapData();
    tileMap_ = std::make_unique<Tile::TileMap>(tileMapData);
    tileMap_->Load();
}

void Level::EnableInput(bool enable)
{
    entitySystem_.EnableInput(enable);
}

sf::Vector2u Level::GetSize() const
{
    return tileMap_->GetSize();
}

}  // namespace FA
