/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>

#include "Animation.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

class Animator
{
public:
    Animation Get(FrameType frameType, FaceDirection dir) const;
    void AddAnimation(FrameType frameType, FaceDirection dir, const Animation& animation);

private:
    using Key = std::pair<FrameType, FaceDirection>;
    std::map<Key, Animation> animationInfoMap_;
};

}  // namespace FA
