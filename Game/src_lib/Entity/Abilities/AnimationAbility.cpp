/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationAbility.h"

namespace FA {

namespace Entity {

AnimationAbility::AnimationAbility(std::function<std::string()> getKey, std::function<void(const Animation &)> updateFn)
    : getKey_(getKey)
    , updateFn_(updateFn)
{}

AnimationAbility::~AnimationAbility() = default;

void AnimationAbility::Enter(std::shared_ptr<BasicEvent> event)
{
    auto key = getKey_();
    // if key is in map_
    currentAnimation_ = map_.at(key);
    currentAnimation_.Start();
}

void AnimationAbility::Update(float deltaTime)
{
    if (currentAnimation_.IsValid()) {
        currentAnimation_.Update(deltaTime);
        updateFn_(currentAnimation_);
    }
}

void AnimationAbility::RegisterAnimation(const std::string &name, const Animation &animation)
{
    // check for already registered name
    map_[name] = animation;
}

bool AnimationAbility::AnimationIsCompleted() const
{
    return currentAnimation_.IsValid() ? currentAnimation_.IsCompleted() : true;
}

}  // namespace Entity

}  // namespace FA
