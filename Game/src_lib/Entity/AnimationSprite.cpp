/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationSprite.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

namespace Entity {

AnimationSprite::AnimationSprite(std::function<std::string(StateType stateType)> getKey)
    : getKey_(getKey)
{}

AnimationSprite::~AnimationSprite() = default;

void AnimationSprite::Enter(StateType stateType)
{
    auto key = getKey_(stateType);
    // if key is in map_
    currentAnimation_ = map_.at(key);
    currentAnimation_.ApplyTo(sprite_);
    currentAnimation_.Start();
}

void AnimationSprite::RegisterAnimation(const std::string &name, const Animation &animation)
{
    // check for already registered name
    map_[name] = animation;
}

void AnimationSprite::Update(float deltaTime)
{
    if (currentAnimation_.IsValid()) {
        currentAnimation_.Update(deltaTime);
        currentAnimation_.ApplyTo(sprite_);
    }
}

void AnimationSprite::DrawTo(sf::RenderTarget &renderTarget)
{
    if (currentAnimation_.IsValid()) {
        renderTarget.draw(sprite_);
    }
}

bool AnimationSprite::AnimationIsCompleted() const
{
    return currentAnimation_.IsValid() ? currentAnimation_.IsCompleted() : true;
}

void AnimationSprite::ApplyTo(std::function<void(sf::Sprite &sprite)> applyFn)
{
    // Here setting of position, scale and rotation can be done
    if (currentAnimation_.IsValid()) {
        applyFn(sprite_);
    }
}

}  // namespace Entity

}  // namespace FA
