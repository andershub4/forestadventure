/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelLayer.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Effect/BasicEffect.h"
#include "Level/Level.h"
#include "Message/MessageBus.h"
#include "Scene/Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

LevelLayer::LevelLayer(MessageBus& messageBus, const sf::IntRect& rect, TextureManager& textureManager)
    : BasicLayer(messageBus, rect)
    , cameraManager_(layerTexture_.getSize())
{
    level_ = std::make_unique<Level>(messageBus, textureManager, cameraManager_);
}

LevelLayer::~LevelLayer() = default;

void LevelLayer::OnCreate()
{
    level_->Load();
    auto s = level_->GetMapSize();
    cameraManager_.SetMapSize(s);
    level_->Setup();
}

void LevelLayer::Draw()
{
    level_->Draw(layerTexture_);
    if (effect_) effect_->DrawTo(layerTexture_);
}

void LevelLayer::Update(float deltaTime)
{
    level_->Update(deltaTime);
    cameraManager_.Update(layerTexture_);
    if (effect_) effect_->Update(deltaTime);
}

void LevelLayer::EnableInput(bool enable)
{
    level_->EnableInput(enable);
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
