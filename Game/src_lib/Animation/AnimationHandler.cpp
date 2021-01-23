/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationHandler.h"

#include "Utils/Logger.h"

namespace FA {

AnimationHandler::AnimationHandler(float switchTime)
    : switchTime_(switchTime)
{}

void AnimationHandler::Update(float deltaTime)
{
    if (currentAnimation_) currentAnimation_->Update(deltaTime);
}

void AnimationHandler::ChangeAnimation(FrameType frameType, sf::RectangleShape& rectShape, bool start)
{
    if (frameType != currentFrameType_) {
        currentFrameType_ = frameType;
        currentAnimation_ = CreateAnimation(currentFrameType_, currentDir_, rectShape);
        if (start) Start();
    }
}

void AnimationHandler::ChangeAnimation(FaceDirection dir, sf::RectangleShape& rectShape, bool start)
{
    if (dir != currentDir_) {
        currentDir_ = dir;
        currentAnimation_ = CreateAnimation(currentFrameType_, currentDir_, rectShape);
        if (start) Start();
    }
}

void AnimationHandler::ChangeAnimation(FrameType frameType, FaceDirection dir, sf::RectangleShape& rectShape, bool start)
{
    if (frameType != currentFrameType_ || dir != currentDir_) {
        currentFrameType_ = frameType;
        currentDir_ = dir;
        currentAnimation_ = CreateAnimation(currentFrameType_, currentDir_, rectShape);
        if (start) Start();
    }
}

void AnimationHandler::RegisterAnimationInfo(FrameType frameType, FaceDirection dir, const sf::Texture* texture,
                                             const std::vector<sf::IntRect>& frames, unsigned int defaultFrame,
                                             bool mirrorX)
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

void AnimationHandler::Init(FrameType frameType, FaceDirection dir, sf::RectangleShape& rectShape, bool start)
{
    currentFrameType_ = frameType;
    currentDir_ = dir;
    currentAnimation_ = CreateAnimation(currentFrameType_, currentDir_, rectShape);
    if (start) Start();
}

void AnimationHandler::Start()
{
    if (currentAnimation_) currentAnimation_->Start();
}

void AnimationHandler::Stop()
{
    if (currentAnimation_) currentAnimation_->Stop();
}

std::unique_ptr<Animation> AnimationHandler::CreateAnimation(FrameType frameType, FaceDirection dir,
                                                             sf::RectangleShape& rectShape) const
{
    auto it = animationInfoMap_.find({frameType, dir});
    if (it != animationInfoMap_.end()) {
        auto info = animationInfoMap_.at({frameType, dir});
        return std::make_unique<Animation>(&rectShape, info.texture_, info.frames_, info.defaultFrame_, switchTime_);
    }
    else {
        LOG_ERROR("frameType: ", static_cast<unsigned int>(frameType), " dir: ", static_cast<unsigned int>(dir),
                  " does not exist");
        return nullptr;
    }
}

std::vector<sf::IntRect> AnimationHandler::MirrorX(const std::vector<sf::IntRect>& frames) const
{
    std::vector<sf::IntRect> mirrorFrames;
    for (const auto& frame : frames) {
        mirrorFrames.emplace_back(frame.left + frame.width, frame.top, -frame.width, frame.height);
    }

    return mirrorFrames;
}

}  // namespace FA
