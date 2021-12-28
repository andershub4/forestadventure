/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Effect/BasicEffect.h"
#include "Folder.h"
#include "Level/Level.h"
#include "Message/MessageBus.h"
#include "Scene/Layer.h"
#include "Scene/Transitions/BasicTransition.h"
#include "Tile/TileMapReader.h"

namespace FA {

namespace Scene {

LevelComponent::LevelComponent(MessageBus& messageBus, const Layer& layer, TextureManager& textureManager)
    : BasicComponent(messageBus, layer)
    , messageBus_(messageBus)
    , animationDb_(textureManager)
    , tileMap_(textureManager, scale_)
{}

LevelComponent::~LevelComponent() = default;

void LevelComponent::OnCreate()
{
    animationDb_.Load();

    auto path = GetAssetsPath() + "/map/test.tmx";
    Tile::TileMapReader tileMapReader;
    auto tileMapData = tileMapReader.Parse(path);
    tileMap_.Create(tileMapData);

    level_ = std::make_unique<Level>(messageBus_, layerTexture_, tileMap_, animationDb_);
    level_->Create();
}

void LevelComponent::Draw()
{
    level_->Draw();
    if (effect_) effect_->DrawTo(layerTexture_);
}

void LevelComponent::Update(float deltaTime)
{
    level_->Update(deltaTime);
    if (effect_) effect_->Update(deltaTime);
}

void LevelComponent::EnableInput(bool enable)
{
    level_->EnableInput(enable);
}

void LevelComponent::EnterTransition(const BasicTransition& transition)
{
    sf::Vector2f layerPos = layerTexture_.mapPixelToCoords({0, 0});
    sf::Vector2f layerSize = static_cast<sf::Vector2f>(layerTexture_.getSize());
    effect_ = transition.CreateEffect(layerPos, layerSize);
}

void LevelComponent::ExitTransition(const BasicTransition& transition)
{
    effect_.reset();
}

}  // namespace Scene

}  // namespace FA
