/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SpriteSheet.h"

#include <SFML/Graphics/Texture.hpp>

#include "Logging.h"

namespace FA {

SpriteSheet::SpriteSheet(const sf::Texture* texture, const sf::Vector2u& frameCount)
    : texture_(texture)
    , frameCount_(frameCount)
    , isValid_(true)
{}

std::vector<sf::IntRect> SpriteSheet::MirrorX(const std::vector<sf::IntRect>& frames)
{
    std::vector<sf::IntRect> mirrorFrames;
    for (const auto& frame : frames) {
        mirrorFrames.emplace_back(frame.left + frame.width, frame.top, -frame.width, frame.height);
    }

    return mirrorFrames;
}

SpriteSheet::FrameData SpriteSheet::Scan(const sf::Vector2u& uvCoord, unsigned int nFrames,
                                         unsigned int defaultFrame) const
{
    auto frames = GenerateFrames(uvCoord, nFrames);
    return {texture_, defaultFrame, frames, true};
}

SpriteSheet::SingleFrame SpriteSheet::At(const sf::Vector2u& uvCoord) const
{
    auto frameSize = CalcFrameSize();

    if (frameSize.x > 0 && frameSize.y) {
        int left = static_cast<int>(uvCoord.x * frameSize.x);
        int top = static_cast<int>(uvCoord.y * frameSize.y);
        int width = static_cast<int>(frameSize.x);
        int height = static_cast<int>(frameSize.y);
        sf::IntRect frame = {left, top, width, height};
        return {texture_, frame, true};
    }

    return {};
}

sf::Vector2u SpriteSheet::CalcFrameSize() const
{
    sf::Vector2u textureSize = texture_->getSize();

    if (frameCount_.x > 0 && frameCount_.y > 0)
        return {textureSize.x / frameCount_.x, textureSize.y / frameCount_.y};
    else
        LOG_ERROR("Can't calculate frameSize due to frameCount.x, frameCount.y  ", frameCount_.x, frameCount_.y);

    return {};
}

std::vector<sf::IntRect> SpriteSheet::GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nFrames) const
{
    std::vector<sf::IntRect> frames;
    auto startFrame = At(uvCoord).frame_;

    // build frames from left to right
    for (unsigned int i = 0; i < nFrames; i++) {
        auto frame = startFrame;
        frame.left += i * frame.width;
        frames.push_back(frame);
    }

    return frames;
}

}  // namespace FA
