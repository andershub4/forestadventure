/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Effect/BasicEffect.h"
#include "Level/Level.h"
#include "Message/MessageBus.h"
#include "Scene/Layer.h"
#include "Scene/Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

LevelComponent::LevelComponent(MessageBus& messageBus, const Layer& layer, TextureManager& textureManager)
    : BasicComponent(messageBus, layer)
    , messageBus_(messageBus)
    , cameraManager_(layerTexture_.getSize())
    , textureManager_(textureManager)
{
    level_ = std::make_unique<Level>(messageBus_, textureManager_);
}

LevelComponent::~LevelComponent() = default;

void LevelComponent::OnCreate()
{
    level_->Load();
    auto s = level_->GetMapSize();
    cameraManager_.SetMapSize(s);
    level_->Create(cameraManager_);
}

void LevelComponent::Draw()
{
    level_->Draw(layerTexture_);
    if (effect_) effect_->DrawTo(layerTexture_);
}

void LevelComponent::Update(float deltaTime)
{
    level_->Update(deltaTime);
    cameraManager_.Update(layerTexture_);
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
