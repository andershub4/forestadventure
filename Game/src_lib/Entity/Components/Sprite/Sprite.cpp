/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprite.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Transform/Transform.h"

namespace FA {

namespace Entity {

Sprite::Sprite(const Transform &transform, const AnimationDB &animationDB)
    : animationDB_(animationDB)
{
    Apply(transform);
}

Sprite::~Sprite() = default;

void Sprite::Update(float deltaTime)
{
    animation_.Update(deltaTime);
}

void Sprite::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

void Sprite::Apply(const Transform &transform)
{
    sprite_.setPosition(transform.GetPosition());
    sprite_.setScale(transform.GetScale(), transform.GetScale());
}

void Sprite::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    animation_ = animationDB_.Get(frameType, faceDir, &sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

void Sprite::StartAnimation()
{
    animation_.Start();
}

bool Sprite::AnimationIsCompleted() const
{
    return animation_.IsCompleted();
}

}  // namespace Entity

}  // namespace FA
