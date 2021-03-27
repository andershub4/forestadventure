/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Animation/AnimationFactory.h"
#include "Entity/Components/Sprite/AnimatedSprite.h"
#include "Entity/Components/Sprite/StaticSprite.h"
#include "Entity/Entities/MoleEntity.h"
#include "Entity/Entities/PlayerEntity.h"
#include "Entity/Entities/StaticEntity.h"
#include "Enum/AnimationType.h"
#include "Enum/TileType.h"
#include "Misc/TextureManager.h"
#include "Camera.h"

namespace FA {

Level::Level(TextureManager& textureManager)
    : animationManager_(textureManager), tileSet_(textureManager), tileMap_(tileSet_)
{}

Level::~Level()
{
    entity_->OnDestroy();
    moleEntity_->OnDestroy();
    stoneEntity_->OnDestroy();
}

void Level::Update(float deltaTime)
{
    entity_->Update(deltaTime);
    moleEntity_->Update(deltaTime);
    stoneEntity_->Update(deltaTime);
}

void Level::DrawTo(sf::RenderTarget& renderTarget)
{
    tileMap_.DrawTo(renderTarget);
    entity_->DrawTo(renderTarget);
    moleEntity_->DrawTo(renderTarget);
    stoneEntity_->DrawTo(renderTarget);
}

void Level::Create(MessageBus &messageBus, Camera &camera)
{
    animationManager_.RegisterFactories();

    auto animationFactory = animationManager_.GetFactory(AnimationType::Player);
    auto sprite = std::make_unique<Entity::AnimatedSprite>(64, sf::Vector2u(0, 0), animationFactory);
    auto playerId = GenerateEntityId();
    entity_ =
        std::make_unique<Entity::PlayerEntity>(playerId, messageBus, std::move(sprite), FaceDirection::Down, 120.0f);
    entity_->OnCreate();

    camera.Follow(entity_.get());

    auto moleAnimationFactory = animationManager_.GetFactory(AnimationType::Mole);
    auto moleSprite = std::make_unique<Entity::AnimatedSprite>(48, sf::Vector2u(8 * 32, 8 * 32), moleAnimationFactory);
    auto moleId = GenerateEntityId();
    moleEntity_ =
        std::make_unique<Entity::MoleEntity>(moleId, messageBus, std::move(moleSprite), FaceDirection::Down, 120.0f);
    moleEntity_->OnCreate();

    auto stoneTile = tileSet_.GetTile(TileType::Stone);
    auto stoneSprite =
        std::make_unique<Entity::StaticSprite>(32, sf::Vector2u(8 * 64, 8 * 10), stoneTile.texture_, stoneTile.rect_);
    auto stoneId = GenerateEntityId();
    stoneEntity_ = std::make_unique<Entity::StaticEntity>(stoneId, messageBus, std::move(stoneSprite));
    stoneEntity_->OnCreate();

    tileMap_.Load();
}

void Level::EnableInput(bool enable)
{
    entity_->EnableInput(enable);
    moleEntity_->EnableInput(enable);
    stoneEntity_->EnableInput(enable);
}

sf::Vector2u Level::GetSize() const
{
    return tileMap_.GetSize();
}

Entity::EntityId Level::GenerateEntityId()
{
    return entityId_++;
}

}  // namespace FA