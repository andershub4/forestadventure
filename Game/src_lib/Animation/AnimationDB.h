/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics/Rect.hpp>

#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class Animation;

class AnimationDB
{
public:
    AnimationDB() = default;
    AnimationDB(const AnimationDB&) = default;
    AnimationDB(float switchTime);

    Animation Get(FrameType frameType, FaceDirection dir, sf::Sprite* sprite) const;
    void RegisterAnimationInfo(FrameType frameType, FaceDirection dir, const sf::Texture* texture,
                               const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, bool mirrorX = false);

private:
    struct AnimationInfo
    {
        const sf::Texture* texture_ = nullptr;
        std::vector<sf::IntRect> frames_;
        unsigned int defaultFrame_ = 0;
        float switchTime_ = 0;
    };
    using Key = std::pair<FrameType, FaceDirection>;
    std::map<Key, AnimationInfo> animationInfoMap_;
    float switchTime_ = 0;
    FrameType currentFrameType_ = FrameType::Undefined;
    FaceDirection currentDir_ = FaceDirection::Down;

private:
    std::vector<sf::IntRect> MirrorX(const std::vector<sf::IntRect>& frames) const;
};

}  // namespace FA
