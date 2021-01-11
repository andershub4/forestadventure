/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "AnimationGroup.h"

#include <iostream>

namespace FA {

AnimationGroup::AnimationGroup(float switchTime)
	: switchTime_(switchTime)
{}


void AnimationGroup::RegisterAnimationInfo(FaceDir dir, const sf::Texture* texture, const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, bool mirrorX)
{
	animationInfoMap_[dir] = { texture, mirrorX ? MirrorX(frames) : frames, defaultFrame, switchTime_ };
}


std::unique_ptr<Animation> AnimationGroup::CreateAnimation(FaceDir dir, sf::RectangleShape& rectShape) const
{
	auto it = animationInfoMap_.find(dir);
	if (it != animationInfoMap_.end()) {
		auto info = animationInfoMap_.at(dir);
		return std::make_unique<Animation>(&rectShape, info.texture_, info.frames_, info.defaultFrame_, switchTime_);
	}
	else {
		std::cout << "AnimationGroup::CreateAnimation dir: " << static_cast<unsigned int>(dir) << " does not exist" << std::endl;
		return nullptr;
	}
}


std::vector<sf::IntRect> AnimationGroup::MirrorX(const std::vector<sf::IntRect>& frames) const
{
	std::vector<sf::IntRect> mirrorFrames;
	for (const auto& frame : frames) {
		mirrorFrames.emplace_back(frame.left + frame.width, frame.top, -frame.width, frame.height);
	}

	return mirrorFrames;
}

} // namespace FA