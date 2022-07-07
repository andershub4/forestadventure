/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/PropertyData.h"
#include "Enum/FaceDirection.h"
#include "Logging.h"
#include "Resource/Image.h"

namespace FA {

namespace {

EntityType ObjTypeStrToEnum(const std::string &typeStr)
{
    auto result = EntityType::Unknown;

    if (typeStr == "Mole") {
        result = EntityType::Mole;
    }
    else if (typeStr == "Player") {
        result = EntityType::Player;
    }
    else if (typeStr == "Coin") {
        result = EntityType::Coin;
    }

    return result;
}

FaceDirection FaceDirStrToEnum(const std::string &faceDirStr)
{
    auto result = FaceDirection::Undefined;

    if (faceDirStr == "Up") {
        result = FaceDirection::Up;
    }
    else if (faceDirStr == "Down") {
        result = FaceDirection::Down;
    }
    else if (faceDirStr == "Right") {
        result = FaceDirection::Right;
    }
    else if (faceDirStr == "Left") {
        result = FaceDirection::Left;
    }

    return result;
}

}  // namespace

Level::Level(MessageBus &messageBus, const Tile::TileMap &tileMap, const SheetManager &sheetManager,
             const sf::Vector2u &viewSize)
    : tileMap_(tileMap)
    , cameraManager_(viewSize, tileMap_.GetSize())
    , factory_(messageBus, sheetManager, cameraManager_, tileMap.GetSize())
    , entityManager_(factory_)
{}

Level::~Level() = default;

void Level::Create()
{
    LOG_INFO_ENTER_FUNC();
    CreateBackground();
    CreateEntities();
    cameraManager_.Reset();  // Reset camera after player created the camera
    CreateFringe();
    LOG_INFO_EXIT_FUNC();
}

sf::View Level::GetView()
{
    return cameraManager_.GetView();
}

void Level::Update(float deltaTime)
{
    entityManager_.HandleCreatedEntities();
    cameraManager_.Update(deltaTime);
    entityManager_.Update(deltaTime);
    entityManager_.HandleDeletedEntities();
}

void Level::Draw(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(backgroundSprite_);
    entityManager_.DrawTo(renderTarget);
    for (const auto &tile : fringeLayer_) {
        renderTarget.draw(tile);
    }
}

void Level::CreateBackground()
{
    LOG_INFO("Create background texture");
    backgroundTexture_.create(tileMap_.GetSize().x, tileMap_.GetSize().y);
    for (const auto &tileData : tileMap_.GetLayer("Ground Layer 1")) {
        CreateBackgroundTile(tileData);
    }
    for (const auto &tileData : tileMap_.GetLayer("Ground Layer 2")) {
        CreateBackgroundTile(tileData);
    }
    backgroundTexture_.display();
    backgroundSprite_.setTexture(backgroundTexture_.getTexture());
}

void Level::CreateEntities()
{
    LOG_INFO("Create entities");
    for (const auto &objectData : tileMap_.GetObjectGroup("Object Layer 1")) {
        CreateObjectEntity(objectData);
    }
    for (const auto &tileData : tileMap_.GetLayer("Dynamic Layer 1")) {
        CreateTileEntity(tileData);
    }
    entityManager_.HandleCreatedEntities();
}

void Level::CreateFringe()
{
    LOG_INFO("Create fringe");
    for (const auto &tileData : tileMap_.GetLayer("Fringe Layer")) {
        CreateFringeTile(tileData);
    }
}

void Level::CreateBackgroundTile(const Tile::TileMap::TileData &data)
{
    Image image(data.frameData_.frame_);
    sf::Sprite tile;
    image.ApplyTo(tile);
    tile.setPosition(static_cast<float>(data.x_), static_cast<float>(data.y_));
    backgroundTexture_.draw(tile);
}

void Level::CreateObjectEntity(const Tile::TileMap::ObjectData &data)
{
    Entity::PropertyData d;
    d.position_ = sf::Vector2f(static_cast<float>(data.x_), static_cast<float>(data.y_));
    d.properties_ = data.properties_;
    entityManager_.CreateEntity(ObjTypeStrToEnum(data.typeStr_), d);
}

void Level::CreateTileEntity(const Tile::TileMap::TileData &data)
{
    Entity::PropertyData d;
    d.position_ = sf::Vector2f(static_cast<float>(data.x_), static_cast<float>(data.y_));
    d.frames_ = data.frameData_.frames_;
    d.frame_ = data.frameData_.frame_;
    entityManager_.CreateEntity(EntityType::Tile, d);
}

void Level::CreateFringeTile(const Tile::TileMap::TileData &data)
{
    Image image(data.frameData_.frame_);
    sf::Sprite tile;
    image.ApplyTo(tile);
    tile.setPosition(static_cast<float>(data.x_), static_cast<float>(data.y_));
    fringeLayer_.push_back(tile);
}

}  // namespace FA
