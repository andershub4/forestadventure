/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>

#include "Animation.h"

namespace FA {

class AnimationHandler
{
public:
    enum class FrameType { Undefined, Idle, Move, Attack };
    enum class FaceDir { Up, Right, Down, Left };

    AnimationHandler() = default;
    AnimationHandler(float switchTime);

    void Update(float deltaTime);
    void SetAnimation(FrameType frameType, FaceDir dir, sf::RectangleShape& rectShape, bool start);
    void RegisterAnimationInfo(FrameType frameType, FaceDir dir, const sf::Texture* texture,
                               const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, bool mirrorX = false);

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
    using Key = std::pair<FrameType, FaceDir>;
    std::map<Key, AnimationInfo> animationInfoMap_;
    float switchTime_ = 0;
    std::unique_ptr<Animation> currentAnimation_ = nullptr;
    FrameType currentFrameType_ = FrameType::Undefined;
    FaceDir currentDir_ = FaceDir::Down;

private:
    std::unique_ptr<Animation> CreateAnimation(FrameType frameType, FaceDir dir, sf::RectangleShape& rectShape) const;
    std::vector<sf::IntRect> MirrorX(const std::vector<sf::IntRect>& frames) const;
};

}  // namespace FA
