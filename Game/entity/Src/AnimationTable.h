/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "Resource/Animation.h"

namespace FA {

namespace Entity {

class AnimationTable
{
public:
    AnimationTable(std::function<std::string()> keyFn);
    ~AnimationTable();

    void RegisterAnimation(const std::string& key, const Shared::Animation& animation);
    Shared::Animation GetAnimation() const;

private:
    std::unordered_map<std::string, Shared::Animation> map_;
    std::function<std::string()> keyFn_;
};

}  // namespace Entity

}  // namespace FA
