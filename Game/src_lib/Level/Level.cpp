/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/AttributeData.h"
#include "Folder.h"
#include "Logging.h"
#include "Resource/Image.h"
#include "Resource/SheetData.h"
#include "Resource/SheetId.h"
#include "Tile/TileMapReader.h"

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
    {SheetId::Arrow, "sprites/misc/arrow.png", {1, 1}}};

EntityType ObjTypeStrToEnum(const std::string &typeStr)
{
    auto result = EntityType::Unknown;

    if (typeStr == "Mole") {
        result = EntityType::Mole;
    }
    else if (typeStr == "Player") {
        result = EntityType::Player;
    }

    return result;
}

FaceDirection FaceDirStrToEnum(const std::string &faceDirStr)
{
    auto result = FaceDirection::Down;

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

Level::Level(MessageBus &messageBus, TextureManager &textureManager, CameraManager &cameraManager)
    : factory_(messageBus)
    , sheetManager_(textureManager)
    , tileMap_(sheetManager_, scale_)
    , entityManager_(factory_, cameraManager, sheetManager_)

{}

Level::~Level() = default;

void Level::Load()
{
    auto path = GetAssetsPath() + "/map/simpletest.tmx";
    Tile::TileMapReader tileMapReader;
    auto tileMapData = tileMapReader.Parse(path);
    tileMap_.Load(tileMapData);
    auto sheetPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/";

    for (const auto &sheetData : textureSheets) {
        sheetManager_.LoadSheet(sheetPath, sheetData);
    }
}

void Level::Create()
{
    LOG_INFO_ENTER_FUNC();
    tileMap_.Setup();
    CreateBackground();
    CreateEntities();
    CreateFringe();
    LOG_INFO_EXIT_FUNC();
}

void Level::Update(float deltaTime)
{
    entityManager_.HandleCreatedEntities();
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

void Level::EnableInput(bool enable)
{
    entityManager_.EnableInput(enable);
}

sf::Vector2u Level::GetMapSize() const
{
    return tileMap_.GetSize();
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
    Image image(data.frameData_.frame_, 0.0);
    sf::Sprite tile;
    image.ApplyTo(tile);
    tile.setPosition(static_cast<sf::Vector2f>(data.position_));
    tile.setScale(static_cast<float>(scale_), static_cast<float>(scale_));
    backgroundTexture_.draw(tile);
}

void Level::CreateObjectEntity(const Tile::TileMap::ObjectData &data)
{
    Entity::AttributeData d;
    d.position_ = static_cast<sf::Vector2f>(data.position_);
    d.faceDir_ = FaceDirStrToEnum(data.faceDirStr_);
    d.velocity_ = constant::Entity::stdVelocity;
    d.scale_ = static_cast<float>(data.scale_);
    entityManager_.CreateEntity(ObjTypeStrToEnum(data.typeStr_), d);
}

void Level::CreateTileEntity(const Tile::TileMap::TileData &data)
{
    Entity::AttributeData d;
    d.position_ = static_cast<sf::Vector2f>(data.position_);
    d.faceDir_ = FaceDirection::Undefined;
    d.scale_ = static_cast<float>(data.scale_);
    d.frames_ = data.frameData_.frames_;
    d.frame_ = data.frameData_.frame_;
    entityManager_.CreateEntity(EntityType::Tile, d);
}

void Level::CreateFringeTile(const Tile::TileMap::TileData &data)
{
    Image image(data.frameData_.frame_, 0.0);
    sf::Sprite tile;
    image.ApplyTo(tile);
    tile.setPosition(static_cast<sf::Vector2f>(data.position_));
    tile.setScale(static_cast<float>(scale_), static_cast<float>(scale_));
    fringeLayer_.push_back(tile);
}

}  // namespace FA
