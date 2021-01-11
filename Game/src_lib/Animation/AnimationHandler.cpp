/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "AnimationHandler.h"

#include <iostream>

namespace FA {

AnimationHandler::AnimationHandler(float switchTime)
	: switchTime_(switchTime)
{}


void AnimationHandler::Update(float deltaTime)
{
	if (currentAnimation_) currentAnimation_->Update(deltaTime);
}


void AnimationHandler::SetAnimation(FrameType frameType, FaceDir dir, sf::RectangleShape& rectShape, bool start)
{
	if (frameType != currentFrameType_ || currentDir_ != dir) {
		currentFrameType_ = frameType;
		currentDir_ = dir;
		currentAnimation_ = CreateAnimation(frameType, dir, rectShape);
		if (start) Start();
	}
}


void AnimationHandler::RegisterAnimationInfo(FrameType frameType, FaceDir dir, const sf::Texture* texture, const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, bool mirrorX)
{
	auto it = animationInfoMap_.find({ frameType, dir });
	if (it != animationInfoMap_.end()) {
		std::cout << "AnimationHandler::RegisterAnimationInfo frameType: " << static_cast<unsigned int>(frameType) << " dir: " << static_cast<unsigned int>(dir) << " is already registered" << std::endl;
	}
	else {
		animationInfoMap_[{frameType, dir}] = { texture, mirrorX ? MirrorX(frames) : frames, defaultFrame, switchTime_ };
	}
}


void AnimationHandler::Start()
{
	if (currentAnimation_) currentAnimation_->Start();
}


void AnimationHandler::Stop()
{
	if (currentAnimation_) currentAnimation_->Stop();
}


std::unique_ptr<Animation> AnimationHandler::CreateAnimation(FrameType frameType, FaceDir dir, sf::RectangleShape& rectShape) const
{
	auto it = animationInfoMap_.find({ frameType, dir });
	if (it != animationInfoMap_.end()) {
		auto info = animationInfoMap_.at({ frameType, dir });
		return std::make_unique<Animation>(&rectShape, info.texture_, info.frames_, info.defaultFrame_, switchTime_);
	}
	else {
		std::cout << "AnimationHandler::CreateAnimation frameType: " << static_cast<unsigned int>(frameType) << " dir: " << static_cast<unsigned int>(dir) << " does not exist" << std::endl;
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

} // namespace FA