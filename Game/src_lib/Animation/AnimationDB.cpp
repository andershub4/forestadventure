/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationDB.h"

#include "Animation.h"
#include "Logging.h"

namespace FA {

AnimationDB::AnimationDB(float switchTime)
    : switchTime_(switchTime)
{}

void AnimationDB::RegisterAnimationInfo(FrameType frameType, FaceDirection dir, const sf::Texture* texture,
                                        const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, bool mirrorX)
{
    auto it = animationInfoMap_.find({frameType, dir});
    if (it != animationInfoMap_.end()) {
        LOG_WARN("frameType: ", static_cast<unsigned int>(frameType), " dir: ", static_cast<unsigned int>(dir),
                 " is already registered");
    }
    else {
        animationInfoMap_[{frameType, dir}] = {texture, mirrorX ? MirrorX(frames) : frames, defaultFrame, switchTime_};
    }
}

Animation AnimationDB::Get(FrameType frameType, FaceDirection dir, sf::Sprite* sprite) const
{
    auto it = animationInfoMap_.find({frameType, dir});
    if (it != animationInfoMap_.end()) {
        auto info = animationInfoMap_.at({frameType, dir});
        return Animation(sprite, info.texture_, info.frames_, info.defaultFrame_, switchTime_);
    }
    else {
        LOG_ERROR("frameType: ", static_cast<unsigned int>(frameType), " dir: ", static_cast<unsigned int>(dir),
                  " does not exist");
        return Animation();
    }
}

std::vector<sf::IntRect> AnimationDB::MirrorX(const std::vector<sf::IntRect>& frames) const
{
    std::vector<sf::IntRect> mirrorFrames;
    for (const auto& frame : frames) {
        mirrorFrames.emplace_back(frame.left + frame.width, frame.top, -frame.width, frame.height);
    }

    return mirrorFrames;
}

}  // namespace FA
