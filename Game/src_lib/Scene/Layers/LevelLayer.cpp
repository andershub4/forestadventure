/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelLayer.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Effect/BasicEffect.h"
#include "Folder.h"
#include "Level/Level.h"
#include "Resource/SheetData.h"
#include "Resource/SheetId.h"
#include "Scene/Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

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
}

LevelLayer::LevelLayer(MessageBus& messageBus, const sf::IntRect& rect, TextureManager& textureManager)
    : BasicLayer(messageBus, rect)
    , sheetManager_(textureManager)
    , messageBus_(messageBus)
    , tileMap_(sheetManager_)
{}

LevelLayer::~LevelLayer() = default;

void LevelLayer::OnLoad()
{
    auto path = GetAssetsPath() + "/map/simpletest.tmx";
    tileMap_.Load(path);
    tileMap_.Setup();

    auto sheetPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/";
    for (const auto& sheetData : textureSheets) {
        sheetManager_.LoadSheet(sheetPath, sheetData);
    }
}

void LevelLayer::OnCreate()
{
    auto viewSize = layerTexture_.getSize();
    level_ = std::make_unique<Level>(messageBus_, tileMap_, sheetManager_, viewSize);
    level_->Create();
}

void LevelLayer::Draw()
{
    level_->Draw(layerTexture_);
    auto view = level_->GetView();
    layerTexture_.setView(view);
    if (effect_) effect_->DrawTo(layerTexture_);
}

void LevelLayer::Update(float deltaTime)
{
    level_->Update(deltaTime);
    if (effect_) effect_->Update(deltaTime);
}

void LevelLayer::EnterTransition(const BasicTransition& transition)
{
    sf::Vector2f layerPos = layerTexture_.mapPixelToCoords({0, 0});
    sf::Vector2f layerSize = static_cast<sf::Vector2f>(layerTexture_.getSize());
    effect_ = transition.CreateEffect(layerPos, layerSize);
}

void LevelLayer::ExitTransition(const BasicTransition& transition)
{
    effect_.reset();
}

}  // namespace Scene

}  // namespace FA
