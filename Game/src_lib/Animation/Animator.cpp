/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animator.h"

#include "Logging.h"

namespace FA {

void Animator::AddAnimation(const std::string &key, const Animation &animation)
{
    auto it = map_.find(key);
    if (it != map_.end()) {
        LOG_WARN("key: ", key, " is already registered");
    }
    else {
        map_[key] = animation;
    }
}

Animation Animator::GetAnimation(const std::string &key) const
{
    auto it = map_.find(key);
    if (it != map_.end()) {
        return map_.at(key);
    }
    else {
        LOG_ERROR("key: ", key, " does not exist");
        return Animation();
    }
}

}  // namespace FA
