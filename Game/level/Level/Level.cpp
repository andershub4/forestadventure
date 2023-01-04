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
#include "Folder.h"
#include "Logging.h"
#include "Resource/Image.h"
#include "Resource/SheetData.h"
#include "Resource/SheetId.h"

namespace FA {

namespace {

const std::vector<SheetData> textureSheets = {
    {SheetId::HeroWalkSide, "spritesheets/hero/walk/hero-walk-side.png", {6, 1}},
    {SheetId::HeroWalkFront, "spritesheets/hero/walk/hero-walk-front.png", {6, 1}},
    {SheetId::HeroWalkBack, "spritesheets/hero/walk/hero-back-walk.png", {6, 1}},
    {SheetId::HeroAttackSide, "spritesheets/hero/attack/hero-attack-side.png", {3, 1}},
    {SheetId::HeroAttackFront, "spritesheets/hero/attack/hero-attack-front.png", {3, 1}},
    {SheetId::HeroAttackBack, "spritesheets/hero/attack/hero-attack-back.png", {3, 1}},
    {SheetId::HeroAttackWeaponSide, "spritesheets/hero/attack-weapon/hero-attack-side-weapon.png", {3, 1}},
    {SheetId::HeroAttackWeaponFront, "spritesheets/hero/attack-weapon/hero-attack-front-weapon.png", {3, 1}},
    {SheetId::HeroAttackWeaponBack, "spritesheets/hero/attack-weapon/hero-attack-back-weapon.png", {3, 1}},
    {SheetId::HeroIdleSide, "spritesheets/hero/idle/hero-idle-side.png", {1, 1}},
    {SheetId::HeroIdleFront, "spritesheets/hero/idle/hero-idle-front.png", {1, 1}},
    {SheetId::HeroIdleBack, "spritesheets/hero/idle/hero-idle-back.png", {1, 1}},
    {SheetId::MoleWalkSide, "spritesheets/mole/walk/mole-walk-side.png", {4, 1}},
    {SheetId::MoleWalkFront, "spritesheets/mole/walk/mole-walk-front.png", {4, 1}},
    {SheetId::MoleWalkBack, "spritesheets/mole/walk/mole-walk-back.png", {4, 1}},
    {SheetId::MoleIdleSide, "spritesheets/mole/idle/mole-idle-side.png", {1, 1}},
    {SheetId::MoleIdleFront, "spritesheets/mole/idle/mole-idle-front.png", {1, 1}},
    {SheetId::MoleIdleBack, "spritesheets/mole/idle/mole-idle-back.png", {1, 1}},
    {SheetId::Arrow, "sprites/misc/arrow.png", {1, 1}},
    {SheetId::Coin, "spritesheets/misc/coin.png", {4, 1}}};

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

Level::Level(MessageBus &messageBus, TextureManager &textureManager, const sf::Vector2u &viewSize)
    : sheetManager_(textureManager)
    , tileMap_(sheetManager_)
    , cameraManager_(viewSize)
    , factory_(messageBus, sheetManager_, *this)
    , entityManager_(factory_)
    , spawnManager_(entityManager_)
{}

Level::~Level() = default;

void Level::Load(const std::string &levelName)
{
    LoadTileMap(levelName);
    LoadEntitySheets();
}

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

void Level::SpawnEntity(EntityType entityType, FaceDirection faceDirection, const sf::Vector2f &position)
{
    spawnManager_.Spawn(entityType, position, faceDirection);
}

void Level::DeleteEntity(Entity::EntityId id)
{
    entityManager_.DeleteEntity(id);
}

sf::FloatRect Level::GetMapRect() const
{
    return mapRect_;
}

void Level::AddCamera(const sf::Vector2f &trackingPoint)
{
    cameraManager_.Track(trackingPoint, tileMap_.GetSize());
}

void Level::LoadEntitySheets()
{
    auto sheetPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/";
    for (const auto &sheetData : textureSheets) {
        sheetManager_.LoadSheet(sheetPath, sheetData);
    }
}

void Level::LoadTileMap(const std::string &levelName)
{
    auto path = GetAssetsPath() + "/map/" + levelName;
    tileMap_.Load(path);
    tileMap_.Setup();
    mapRect_ = sf::FloatRect({0.0f, 0.0f}, static_cast<sf::Vector2f>(tileMap_.GetSize()));
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
    Image image(data.frame_);
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
    d.frames_ = data.frames_;
    d.frame_ = data.frame_;
    entityManager_.CreateEntity(EntityType::Tile, d);
}

void Level::CreateFringeTile(const Tile::TileMap::TileData &data)
{
    Image image(data.frame_);
    sf::Sprite tile;
    image.ApplyTo(tile);
    tile.setPosition(static_cast<float>(data.x_), static_cast<float>(data.y_));
    fringeLayer_.push_back(tile);
}

}  // namespace FA
