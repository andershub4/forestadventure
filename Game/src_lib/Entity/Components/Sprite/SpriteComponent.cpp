/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SpriteComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Transform/TransformComponent.h"

namespace FA {

namespace Entity {

SpriteComponent::SpriteComponent(const TransformComponent &transform, const Animator &animator)
    : animator_(animator)
{
    Apply(transform);
}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::Update(float deltaTime)
{
    animation_.Update(deltaTime);
    animation_.ApplyTo(sprite_);
}

void SpriteComponent::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

void SpriteComponent::Apply(const TransformComponent &transform)
{
    sprite_.setPosition(transform.GetPosition());
    sprite_.setScale(transform.GetScale(), transform.GetScale());
}

void SpriteComponent::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    animation_ = animator_.Get(frameType, faceDir);
    animation_.ApplyTo(sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

void SpriteComponent::StartAnimation()
{
    animation_.Start();
}

bool SpriteComponent::AnimationIsCompleted() const
{
    return animation_.IsCompleted();
}

}  // namespace Entity

}  // namespace FA
