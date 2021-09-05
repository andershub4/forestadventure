/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/ComponentData.h"
#include "Entity/ComponentHandler.h"
#include "Entity/Entities/BasicEntity.h"
#include "Entity/EntityTextures.h"
#include "Folder.h"
#include "Logging.h"
#include "Resource/TextureManager.h"
#include "Tile/TileMapReader.h"

namespace FA {

Level::Level(MessageBus &messageBus, TextureManager &textureManager, sf::RenderTarget &renderTarget)
    : textureManager_(textureManager)
    , tileMap_(textureManager, scale_)
    , renderTarget_(renderTarget)
    , camera_(renderTarget_.getSize())
    , factory_(messageBus)
    , entityManager_(factory_)
    , animationDb_(textureManager_)
{}

Level::~Level() = default;

void Level::Load(const std::string &mapPath)
{
    LOG_INFO_ENTER_FUNC();

    LOG_INFO("Load entity textures");
    auto ssPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/spritesheets/";
    for (const auto &v : Entity::textures) {
        auto p = ssPath + v.path_;
        textureManager_.Add(v.name_, p);
    }

    animationDb_.Init();

    LOG_INFO("Create tile map");
    Tile::TileMapReader tileMapReader;
    auto tileMapData = tileMapReader.Parse(mapPath);
    tileMap_.Create(tileMapData);

    LOG_INFO("Create entities");
    for (const auto &objectData : tileMap_.GetObjectGroup("Object Layer 1")) {
        Entity::ComponentData componentData;
        componentData.entityType_ = objectData.type_;
        componentData.position_ = static_cast<sf::Vector2f>(objectData.position_);
        componentData.faceDir_ = objectData.faceDir_;
        componentData.velocity_ = 120.0;
        componentData.scale_ = static_cast<float>(scale_);
        auto entity = entityManager_.Create(objectData.type_, Entity::ComponentHandler(componentData));
        if (objectData.type_ == EntityType::Player) {
            camera_.Follow(entity);
        }
    }

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
