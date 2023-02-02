/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Camera.h"
#include "Constant/Entity.h"
#include "Entity/PropertyData.h"
#include "Enum/FaceDirection.h"
#include "Folder.h"
#include "Logging.h"
#include "MapData.h"
#include "Resource/Image.h"
#include "Resource/SheetData.h"
#include "Resource/SheetId.h"

namespace FA {

namespace {

const std::vector<Shared::SheetData> textureSheets = {
    {Shared::SheetId::HeroWalkSide, "spritesheets/hero/walk/hero-walk-side.png", {6, 1}},
    {Shared::SheetId::HeroWalkFront, "spritesheets/hero/walk/hero-walk-front.png", {6, 1}},
    {Shared::SheetId::HeroWalkBack, "spritesheets/hero/walk/hero-back-walk.png", {6, 1}},
    {Shared::SheetId::HeroAttackSide, "spritesheets/hero/attack/hero-attack-side.png", {3, 1}},
    {Shared::SheetId::HeroAttackFront, "spritesheets/hero/attack/hero-attack-front.png", {3, 1}},
    {Shared::SheetId::HeroAttackBack, "spritesheets/hero/attack/hero-attack-back.png", {3, 1}},
    {Shared::SheetId::HeroAttackWeaponSide, "spritesheets/hero/attack-weapon/hero-attack-side-weapon.png", {3, 1}},
    {Shared::SheetId::HeroAttackWeaponFront, "spritesheets/hero/attack-weapon/hero-attack-front-weapon.png", {3, 1}},
    {Shared::SheetId::HeroAttackWeaponBack, "spritesheets/hero/attack-weapon/hero-attack-back-weapon.png", {3, 1}},
    {Shared::SheetId::HeroIdleSide, "spritesheets/hero/idle/hero-idle-side.png", {1, 1}},
    {Shared::SheetId::HeroIdleFront, "spritesheets/hero/idle/hero-idle-front.png", {1, 1}},
    {Shared::SheetId::HeroIdleBack, "spritesheets/hero/idle/hero-idle-back.png", {1, 1}},
    {Shared::SheetId::MoleWalkSide, "spritesheets/mole/walk/mole-walk-side.png", {4, 1}},
    {Shared::SheetId::MoleWalkFront, "spritesheets/mole/walk/mole-walk-front.png", {4, 1}},
    {Shared::SheetId::MoleWalkBack, "spritesheets/mole/walk/mole-walk-back.png", {4, 1}},
    {Shared::SheetId::MoleIdleSide, "spritesheets/mole/idle/mole-idle-side.png", {1, 1}},
    {Shared::SheetId::MoleIdleFront, "spritesheets/mole/idle/mole-idle-front.png", {1, 1}},
    {Shared::SheetId::MoleIdleBack, "spritesheets/mole/idle/mole-idle-back.png", {1, 1}},
    {Shared::SheetId::Arrow, "sprites/misc/arrow.png", {1, 1}},
    {Shared::SheetId::Coin, "spritesheets/misc/coin.png", {4, 1}}};

EntityType ObjTypeStrToEnum(const std::string &str)
{
    static std::unordered_map<std::string, EntityType> map{
        {"Mole", EntityType::Mole}, {"Player", EntityType::Player}, {"Coin", EntityType::Coin}};
    auto it = map.find(str);
    if (it != map.end()) {
        return map.at(str);
    }

    return EntityType::Unknown;
}

FaceDirection FaceDirStrToEnum(const std::string &str)
{
    static std::unordered_map<std::string, FaceDirection> map{{"Up", FaceDirection::Up},
                                                              {"Down", FaceDirection::Down},
                                                              {"Right", FaceDirection::Right},
                                                              {"Left", FaceDirection::Left}};
    auto it = map.find(str);
    if (it != map.end()) {
        return map.at(str);
    }

    return FaceDirection::Undefined;
}

}  // namespace

Level::Level(Shared::MessageBus &messageBus, Shared::TextureManager &textureManager, const sf::Vector2u &viewSize)
    : sheetManager_(textureManager)
    , tileMap_(sheetManager_)
    , viewSize_(viewSize)
    , factory_(messageBus, sheetManager_, cameraManager_, *this)
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
    cameraManager_.CreateCamera(viewSize_, tileMap_.GetSize());
    CreateEntities();
    CreateFringe();
    LOG_INFO_EXIT_FUNC();
}

sf::View Level::GetView()
{
    auto &camera = cameraManager_.GetCamera();
    return camera.GetView();
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
    auto mapRect = sf::FloatRect({0.0f, 0.0f}, static_cast<sf::Vector2f>(tileMap_.GetSize()));
    Shared::MapData md{mapRect};
    spawnManager_.Spawn(entityType, position, md, faceDirection);
}

void Level::DeleteEntity(Entity::EntityId id)
{
    entityManager_.DeleteEntity(id);
}

sf::FloatRect Level::GetMapRect() const
{
    return mapRect_;
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

void Level::CreateBackgroundTile(const TileMap::TileData &data)
{
    Shared::Image image(data.graphic_.image_);
    sf::Sprite tile;
    image.ApplyTo(tile);
    tile.setPosition(static_cast<float>(data.x_), static_cast<float>(data.y_));
    backgroundTexture_.draw(tile);
}

void Level::CreateObjectEntity(const TileMap::ObjectData &data)
{
    Entity::PropertyData d;
    d.position_ = sf::Vector2f(static_cast<float>(data.x_), static_cast<float>(data.y_));
    d.properties_ = data.properties_;
    auto mapRect = sf::FloatRect({0.0f, 0.0f}, static_cast<sf::Vector2f>(tileMap_.GetSize()));
    Shared::MapData md{mapRect};
    entityManager_.CreateEntity(ObjTypeStrToEnum(data.typeStr_), d, md);
}

void Level::CreateTileEntity(const TileMap::TileData &data)
{
    Entity::PropertyData d;
    d.position_ = sf::Vector2f(static_cast<float>(data.x_), static_cast<float>(data.y_));
    d.graphic_ = data.graphic_;
    auto mapRect = sf::FloatRect({0.0f, 0.0f}, static_cast<sf::Vector2f>(tileMap_.GetSize()));
    Shared::MapData md{mapRect};
    entityManager_.CreateEntity(EntityType::Tile, d, md);
}

void Level::CreateFringeTile(const TileMap::TileData &data)
{
    Shared::Image image(data.graphic_.image_);
    sf::Sprite tile;
    image.ApplyTo(tile);
    tile.setPosition(static_cast<float>(data.x_), static_cast<float>(data.y_));
    fringeLayer_.push_back(tile);
}

}  // namespace FA
