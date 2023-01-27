/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationAbility.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Logging.h"

namespace FA {

namespace Entity {

AnimationAbility::AnimationAbility(std::function<std::string()> getKey,
                                   std::function<void(const Shared::Animation &)> updateFn, bool center)
    : getKey_(getKey)
    , updateFn_(updateFn)
    , center_(center)
{}

AnimationAbility::AnimationAbility(std::function<std::string()> getKey, bool center)
    : getKey_(getKey)
    , updateFn_([](const Shared::Animation &) {})
    , center_(center)
{}

AnimationAbility::~AnimationAbility() = default;

void AnimationAbility::Enter()
{
    auto key = getKey_();
    if (map_.find(key) != map_.end()) {
        currentAnimation_ = map_.at(key);
        currentAnimation_.Start();
    }
    else {
        LOG_ERROR("Could not find key: %s", key.c_str());
    }
}

void AnimationAbility::Update(float deltaTime)
{
    if (currentAnimation_.IsValid()) {
        currentAnimation_.Update(deltaTime);
        currentAnimation_.ApplyTo(sprite_);
        if (center_) {
            sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
        }
        updateFn_(currentAnimation_);
    }
}

void AnimationAbility::SetPosition(const sf::Vector2f &position)
{
    sprite_.setPosition(position);
}

void AnimationAbility::SetRotation(float rot)
{
    sprite_.setRotation(rot);
}

void AnimationAbility::RegisterAnimation(const std::string &name, const Shared::Animation &animation)
{
    if (map_.find(name) == map_.end()) {
        map_[name] = animation;
    }
    else {
        LOG_ERROR("name: %s already exist", name.c_str());
    }
}

void AnimationAbility::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

}  // namespace Entity

}  // namespace FA
