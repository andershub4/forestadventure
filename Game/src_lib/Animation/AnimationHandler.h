/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>

#include "Animation.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

class AnimationHandler
{
public:
    AnimationHandler() = default;
    AnimationHandler(float switchTime);

    void Update(float deltaTime);
    void ChangeAnimation(FrameType frameType, sf::RectangleShape& rectShape, bool start = true);
    void ChangeAnimation(FaceDirection dir, sf::RectangleShape& rectShape, bool start = true);
    void RegisterAnimationInfo(FrameType frameType, FaceDirection dir, const sf::Texture* texture,
                               const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, bool mirrorX = false);
    void Init(FrameType frameType, FaceDirection dir, sf::RectangleShape& rectShape, bool start = false);

    void Start();
    void Stop();

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
    std::unique_ptr<Animation> currentAnimation_ = nullptr;
    FrameType currentFrameType_ = FrameType::Undefined;
    FaceDirection currentDir_ = FaceDirection::Down;

private:
    std::unique_ptr<Animation> CreateAnimation(FrameType frameType, FaceDirection dir,
                                               sf::RectangleShape& rectShape) const;
    std::vector<sf::IntRect> MirrorX(const std::vector<sf::IntRect>& frames) const;
};

}  // namespace FA
