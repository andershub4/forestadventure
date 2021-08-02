/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <string>

#include "Animation.h"

namespace FA {

class Animator
{
public:
    Animation GetAnimation(const std::string &key) const;
    void AddAnimation(const std::string &key, const Animation &animation);

private:
    std::map<std::string, Animation> map_;
};

}  // namespace FA
