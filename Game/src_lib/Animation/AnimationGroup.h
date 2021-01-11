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

	AnimationGroup() = default;
	AnimationGroup(float switchTime);

	void RegisterAnimationInfo(Dir dir, const sf::Texture* texture, const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, bool mirrorX = false);
	std::unique_ptr<Animation> CreateAnimation(Dir dir, sf::RectangleShape& rectShape) const;

private:
	struct AnimationInfo
	{
		const sf::Texture* texture_ = nullptr;
		std::vector<sf::IntRect> frames_;
		unsigned int defaultFrame_ = 0;
		float switchTime_ = 0;
	};

	std::unordered_map<Dir, AnimationInfo> animationInfoMap_;
	float switchTime_ = 0;

public:
	std::vector<sf::IntRect> MirrorX(const std::vector<sf::IntRect>& frames) const;
};

} // namespace FA