/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "Animation.h"

namespace FA {

Animation::Animation(sf::RectangleShape* rectShape, const sf::Texture* texture, const std::vector<sf::IntRect>& frames, unsigned int defaultFrame, float switchTime)
	: rectShape_(rectShape), texture_(texture), frames_(frames), switchTime_(switchTime), time_(0.0), defaultFrame_(defaultFrame), iFrame_(defaultFrame)
{
	nFrames_ = frames.size();
	rectShape_->setTexture(texture_);
	rectShape_->setTextureRect(frames_[defaultFrame_]);
}


void Animation::Update(float deltaTime)
{
	if (!isStopped_ && nFrames_ > 1) {
		time_ += deltaTime;

		while (time_ >= switchTime_) {
			time_ -= switchTime_;
			++iFrame_ %= nFrames_;
		}

		rectShape_->setTextureRect(frames_[iFrame_]);
	}
}


void Animation::Start()
{
	isStopped_ = false;
}


void Animation::Stop()
{
	isStopped_ = true;
	iFrame_ = defaultFrame_;
}

} // namespace FA