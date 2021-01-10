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


void AnimationGroup::AddAnimation(Dir dir, const sf::Texture* texture, const std::vector<sf::IntRect>& frames, unsigned int defaultFrame)
{
	animationMap_[dir] = std::make_unique<Animation>(texture, frames, defaultFrame, switchTime_);
}


Animation* AnimationGroup::GetAnimation(Dir dir)
{
	auto it = animationMap_.find(dir);
	if (it != animationMap_.end()) {
		return animationMap_.at(dir).get();
	}
	else {
		std::cout << "AnimationGroup::GetAnimation dir: " << static_cast<unsigned int>(dir) << " does not exist" << std::endl;
		return nullptr;
	}
}

} // namespace FA