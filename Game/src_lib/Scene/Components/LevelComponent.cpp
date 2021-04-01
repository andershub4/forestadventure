/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Effect/BasicEffect.h"
#include "Message/MessageBus.h"
#include "Misc/TextureManager.h"
#include "Scene/Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

LevelComponent::LevelComponent(MessageBus& messageBus, TextureManager& textureManager)
    : BasicComponent(messageBus)
    , level_(messageBus, textureManager)
{
    level_.Create(camera_);
}

LevelComponent::~LevelComponent() = default;

void LevelComponent::Draw()
{
    level_.DrawTo(layerTexture_);
    if (effect_) effect_->DrawTo(layerTexture_);
}

void LevelComponent::Update(float deltaTime)
{
    level_.Update(deltaTime);
    if (effect_) effect_->Update(deltaTime);
    camera_.UpdatePosition(layerTexture_, level_.GetSize());
}

void LevelComponent::EnableInput(bool enable)
{
    level_.EnableInput(enable);
}

void LevelComponent::EnterTransition(const BasicTransition& transition)
{
    auto size = camera_.GetViewSize();
    auto position = camera_.GetPosition();
    position.x = position.x - size.x / 2;
    position.y = position.y - size.y / 2;

    effect_ = transition.CreateEffect(position, size);
}

void LevelComponent::ExitTransition(const BasicTransition& transition)
{
    effect_.reset();
}

}  // namespace Scene

}  // namespace FA
