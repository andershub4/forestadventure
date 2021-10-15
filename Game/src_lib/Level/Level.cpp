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

namespace FA {

Level::Level(MessageBus &messageBus, sf::RenderTarget &renderTarget, const Tile::TileMap &tileMap,
             const AnimationDb &animationDb)
    : tileMap_(tileMap)
    , renderTarget_(renderTarget)
    , cameraManager_(renderTarget.getSize(), tileMap.GetSize())
    , factory_(messageBus)
    , entityManager_(factory_)
    , animationDb_(animationDb)
{}

Level::~Level() = default;

void Level::Create()
{
    LOG_INFO_ENTER_FUNC();

    LOG_INFO("Create entities");
    for (const auto &objectData : tileMap_.GetObjectGroup("Object Layer 1")) {
        Entity::PropertyData data;
        data.position_ = static_cast<sf::Vector2f>(objectData.position_);
        data.faceDir_ = objectData.faceDir_;
        data.velocity_ = 120.0;
        data.scale_ = static_cast<float>(tileMap_.GetScale());
        entityManager_.Create(objectData.type_, data, cameraManager_);
    }

    entityManager_.Awake();
    entityManager_.Init(animationDb_);

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
    cameraManager_.Update(renderTarget_);
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
