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


void AnimationHandler::SetAnimation(FrameType frameType, AnimationGroup::Dir dir, sf::RectangleShape& rectShape, bool start)
{
	auto it = handlerMap_.find(frameType);

	if (it != handlerMap_.end()) {
		//TODO: Set animation only if it differs from current frameType and dir
		currentAnimation_ = handlerMap_.at(frameType).CreateAnimation(dir, rectShape);
		if (start) Start();
	}
	else {
		std::cout << "AnimationHandler::SetAnimation frameType: " << static_cast<unsigned int>(frameType) << " does not exist" << std::endl;
	}
}


AnimationGroup& AnimationHandler::AddAnimationGroup(FrameType frameType)
{
	handlerMap_.insert(std::pair<FrameType, AnimationGroup>(frameType, AnimationGroup(switchTime_)));

	return handlerMap_[frameType];
}


void AnimationHandler::Start()
{
	if (currentAnimation_) currentAnimation_->Start();
}


void AnimationHandler::Stop()
{
	if (currentAnimation_) currentAnimation_->Stop();
}

} // namespace FA