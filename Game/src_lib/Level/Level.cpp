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

}  // namespace

Level::Level(MessageBus &messageBus, TextureManager &textureManager, CameraManager &cameraManager)
    : factory_(messageBus)
    , tileMap_(textureManager, scale_)
    , sheetManager_(textureManager)
    , entityManager_(factory_, cameraManager, sheetManager_)

{}

Level::~Level() = default;

void Level::Load()
{
    auto path = GetAssetsPath() + "/map/test.tmx";
    Tile::TileMapReader tileMapReader;
    auto tileMapData = tileMapReader.Parse(path);
    tileMap_.Create(tileMapData);

    for (const auto &sheetData : textureSheets) {
        sheetManager_.LoadSheet(sheetData);
    }
}

void Level::Create()
{
    LOG_INFO_ENTER_FUNC();

    LOG_INFO("Create entities");

    for (const auto &objectData : tileMap_.GetObjectGroup("Object Layer 1")) {
        Entity::AttributeData data;
        data.position_ = static_cast<sf::Vector2f>(objectData.position_);
        data.faceDir_ = objectData.faceDir_;
        data.velocity_ = constant::Entity::stdVelocity;
        data.scale_ = static_cast<float>(tileMap_.GetScale());
        entityManager_.CreateEntity(objectData.type_, data);
    }

    entityManager_.HandleCreatedEntities();

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

}  // namespace FA
