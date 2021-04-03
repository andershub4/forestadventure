/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimatedSprite.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Animation/Animation.h"
#include "Entity/Components/Movement/Movement.h"

namespace FA {

namespace Entity {

AnimatedSprite::AnimatedSprite(const sf::Vector2u &position, const AnimationFactory &animationFactory)
    : animationFactory_(animationFactory)
{
    sprite_.setPosition(static_cast<sf::Vector2f>(position));
    sprite_.setScale(2, 2);
}

AnimatedSprite::~AnimatedSprite() = default;

void AnimatedSprite::Update(float deltaTime)
{
    if (animation_) animation_->Update(deltaTime);
}

void AnimatedSprite::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

sf::Vector2f AnimatedSprite::GetPosition() const
{
    return sprite_.getPosition();
}

void AnimatedSprite::Move(const Movement &movement)
{
    movement.ApplyTo(&sprite_);
}

void AnimatedSprite::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    animation_ = animationFactory_.Create(frameType, faceDir, &sprite_);
}

void AnimatedSprite::StartAnimation()
{
    if (animation_) animation_->Start();
}

bool AnimatedSprite::AnimationIsCompleted() const
{
    if (animation_) return animation_->IsCompleted();
    return true;
}

}  // namespace Entity

}  // namespace FA
