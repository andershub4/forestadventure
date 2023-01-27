/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationSprite.h"

#include "Logging.h"

namespace FA {

namespace Entity {

AnimationSprite::AnimationSprite(std::function<std::string()> getKey, const std::unordered_map<std::string, Shared::Animation> &animations,
                                   std::function<void(const Shared::Animation &)> updateFn, bool center)
    : getKey_(getKey)
    , map_(animations)
    , updateFn_(updateFn)
    , center_(center)
{}

AnimationSprite::AnimationSprite(std::function<std::string()> getKey,
                                   const std::unordered_map<std::string, Shared::Animation>& animations, bool center)
    : getKey_(getKey)
    , map_(animations)
    , updateFn_([](const Shared::Animation &) {})
    , center_(center)
{}

AnimationSprite::~AnimationSprite() = default;

void AnimationSprite::Enter()
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

void AnimationSprite::Update(float deltaTime)
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

}  // namespace Entity

}  // namespace FA
