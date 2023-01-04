/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationAbility.h"

#include "Logging.h"

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
        updateFn_(currentAnimation_);
    }
}

void AnimationAbility::RegisterAnimation(const std::string &name, const Animation &animation)
{
    if (map_.find(name) == map_.end()) {
        map_[name] = animation;
    }
    else {
        LOG_ERROR("name: %s already exist", name.c_str());
    }
}

bool AnimationAbility::AnimationIsCompleted() const
{
    return currentAnimation_.IsValid() ? currentAnimation_.IsCompleted() : true;
}

}  // namespace Entity

}  // namespace FA
