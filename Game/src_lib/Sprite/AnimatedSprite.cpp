/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimatedSprite.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Animation/Animation.h"
#include "Movement/Movement.h"

namespace FA {

AnimatedSprite::AnimatedSprite(unsigned int size, const sf::Vector2u &position,
                               const AnimationFactory &animationFactory)
    : BasicSprite(size)
    , animationFactory_(animationFactory)
{
    rectShape_.setPosition(static_cast<sf::Vector2f>(position));
    rectShape_.setSize({static_cast<float>(size), static_cast<float>(size)});
}

AnimatedSprite::~AnimatedSprite() = default;

void AnimatedSprite::Update(float deltaTime)
{
    if (animation_) animation_->Update(deltaTime);
}

void AnimatedSprite::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(rectShape_);
}

sf::Vector2f AnimatedSprite::GetPosition() const
{
    return rectShape_.getPosition();
}

void AnimatedSprite::Move(const Movement &movement)
{
    movement.ApplyTo(&rectShape_);
}

void AnimatedSprite::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    animation_ = animationFactory_.Create(frameType, faceDir, &rectShape_);
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

}  // namespace FA
