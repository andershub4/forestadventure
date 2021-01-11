/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#pragma once

#include <memory>

#include "AnimationGroup.h"

namespace FA {

class AnimationHandler
{
public:
	enum class FrameType { Idle, Move, Attack };

	AnimationHandler() = default;
	AnimationHandler(float switchTime);

	void Update(float deltaTime);
	void SetAnimation(FrameType frameType, AnimationGroup::Dir dir, sf::RectangleShape& rectShape, bool start);
	AnimationGroup& AddAnimationGroup(FrameType frameType);
	void Start();
	void Stop();

private:
	std::unordered_map<FrameType, AnimationGroup> handlerMap_;
	float switchTime_ = 0;
	std::unique_ptr<Animation> currentAnimation_ = nullptr;
};

} // namespace FA