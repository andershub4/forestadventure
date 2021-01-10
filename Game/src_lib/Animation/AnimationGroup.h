/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#pragma once

#include <unordered_map>
#include <memory>

#include <SFML/Graphics/Rect.hpp>

#include "Animation.h"

namespace sf
{
class Texture;
}

namespace FA {

class AnimationGroup
{
public:
	enum class Dir { Up, Right, Down, Left };

	AnimationGroup(float switchTime);

	void AddAnimation(Dir dir, const sf::Texture* texture, const std::vector<sf::IntRect>& frames, unsigned int defaultFrame);
	Animation* GetAnimation(Dir dir);

private:
	std::unordered_map<Dir, std::unique_ptr<Animation>> animationMap_;
	float switchTime_ = 0;
};

} // namespace FA