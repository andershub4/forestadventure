/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "SpriteSheet.h"

#include <iostream>

#include <SFML/Graphics/Texture.hpp>

namespace FA {

SpriteSheet::SpriteSheet(const std::string& name, const sf::Texture* texture, const sf::Vector2u& frameCount)
	: texture_(texture), frameCount_(frameCount) 
{}


SpriteSheet::FrameData SpriteSheet::Scan(const sf::Vector2u& uvCoord, unsigned int nFrames, unsigned int defaultFrame) const
{
	unsigned int frameSize = CalcFrameSize();

	if (frameSize > 0) {
		auto frames = GenerateFrames(uvCoord, nFrames, frameSize);
		return { texture_, defaultFrame, frames };
	}

	return {};
}


unsigned int SpriteSheet::CalcFrameSize() const
{
	sf::Vector2u textureSize = texture_->getSize();

	if (frameCount_.x > 0)
		return textureSize.x / frameCount_.x;
	else
		std::cout << "SpriteSheet::CalcFrameSize can't calculate frameSize due to frameCount.x " << frameCount_.x << std::endl;

	return 0;
}


std::vector<sf::IntRect> SpriteSheet::GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nFrames, unsigned int frameSize) const
{
	std::vector<sf::IntRect> frames;
	//build frames from left to right
	for (unsigned int i = 0; i < nFrames; i++) {
		int left = static_cast<int>((uvCoord.x * frameSize) + i * frameSize);
		int top = static_cast<int>(uvCoord.y * frameSize);
		int width = static_cast<int>(frameSize);
		int height = static_cast<int>(frameSize);
		sf::IntRect frame = { left, top, width, height };
		frames.push_back(frame);
	}

	return frames;
}

} // namespace FA