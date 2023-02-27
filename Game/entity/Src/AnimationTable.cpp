/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationTable.h"

#include "Logging.h"

namespace FA {

namespace Entity {

AnimationTable::AnimationTable(std::function<std::string()> keyFn)
    : keyFn_(keyFn)
{}

AnimationTable::~AnimationTable() = default;

Shared::Animation AnimationTable::GetAnimation() const
{
    auto key = keyFn_();
    if (map_.find(key) != map_.end()) {
        return map_.at(key);
    }

    LOG_ERROR("Could not find key: %s", key.c_str());
    return {};
}

void AnimationTable::RegisterAnimation(const std::string& key, const Shared::Animation& animation)
{
    map_[key] = animation;
}

}  // namespace Entity

}  // namespace FA
