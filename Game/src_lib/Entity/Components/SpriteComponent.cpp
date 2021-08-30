/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SpriteComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "FaceDirectionComponent.h"
#include "TransformComponent.h"

namespace FA {

namespace Entity {

SpriteComponent::SpriteComponent(const TransformComponent &transform, const FaceDirectionComponent &faceDirection,
                                 const AnimationComponent &animation)
    : transform_(transform)
    , faceDirection_(faceDirection)
    , animation_(animation)
{
    sprite_.setPosition(transform_.GetPosition());
    sprite_.setScale(transform_.GetScale(), transform_.GetScale());
}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::Update(float deltaTime)
{
    animation_.Update(deltaTime);
    animation_.ApplyTo(sprite_);
    sprite_.setPosition(transform_.GetPosition());
    sprite_.setScale(transform_.GetScale(), transform_.GetScale());
}

void SpriteComponent::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

void SpriteComponent::Set(FrameType frameType)
{
    animation_.SetAnimation(frameType, faceDirection_.GetDirection());
    animation_.ApplyTo(sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

bool SpriteComponent::AnimationIsCompleted() const
{
    return animation_.IsCompleted();
}

}  // namespace Entity

}  // namespace FA
