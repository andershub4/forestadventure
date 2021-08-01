/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animator.h"

#include "Logging.h"

namespace FA {

void Animator::AddAnimation(FrameType frameType, FaceDirection dir, const Animation &animation)
{
    auto it = animationInfoMap_.find({frameType, dir});
    if (it != animationInfoMap_.end()) {
        LOG_WARN("frameType: ", static_cast<unsigned int>(frameType), " dir: ", static_cast<unsigned int>(dir),
                 " is already registered");
    }
    else {
        animationInfoMap_[{frameType, dir}] = animation;
    }
}

Animation Animator::GetAnimation(FrameType frameType, FaceDirection dir) const
{
    auto it = animationInfoMap_.find({frameType, dir});
    if (it != animationInfoMap_.end()) {
        return animationInfoMap_.at({frameType, dir});
    }
    else {
        LOG_ERROR("frameType: ", static_cast<unsigned int>(frameType), " dir: ", static_cast<unsigned int>(dir),
                  " does not exist");
        return Animation();
    }
}

}  // namespace FA
