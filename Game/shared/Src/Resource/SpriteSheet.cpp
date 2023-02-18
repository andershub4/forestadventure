/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Resource/SpriteSheet.h"

#include <SFML/Graphics/Texture.hpp>

#include "Resource/Frame.h"
#include "Logging.h"

namespace FA {

namespace Shared {

SpriteSheet::SpriteSheet(const sf::Texture* texture, const sf::Vector2u& rectCount)
    : texture_(texture)
    , rectCount_(rectCount)
    , isValid_(true)
{}

std::vector<Frame> SpriteSheet::MirrorX(const std::vector<Frame>& frames)
{
    std::vector<Frame> mirrorFrames;

    for (const auto& frame : frames) {
        Frame f = frame;
        f.rect_.left = frame.rect_.left + frame.rect_.width;
        f.rect_.width = -frame.rect_.width;
        mirrorFrames.push_back(f);
    }

    return mirrorFrames;
}

std::vector<Frame> SpriteSheet::Scan(const sf::Vector2u& uvCoord, unsigned int nRects) const
{
    return GenerateFrames(uvCoord, nRects);
}

Frame SpriteSheet::At(const sf::Vector2u& uvCoord) const
{
    auto rectSize = CalcRectSize();

    if (rectSize.x > 0 && rectSize.y > 0) {
        int left = static_cast<int>(uvCoord.x * rectSize.x);
        int top = static_cast<int>(uvCoord.y * rectSize.y);
        int width = static_cast<int>(rectSize.x);
        int height = static_cast<int>(rectSize.y);
        sf::IntRect rect = {left, top, width, height};
        return Frame(texture_, rect);
    }

    return {};
}

sf::Vector2u SpriteSheet::CalcRectSize() const
{
    sf::Vector2u textureSize = texture_->getSize();

    if (rectCount_.x > 0 && rectCount_.y > 0)
        return {textureSize.x / rectCount_.x, textureSize.y / rectCount_.y};
    else
        LOG_ERROR("Can't calculate rectSize due to rectCount.x %u, rectCount.y  %u", rectCount_.x, rectCount_.y);

    return {};
}

std::vector<Frame> SpriteSheet::GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nRects) const
{
    std::vector<Frame> frames;
    auto startFrame = At(uvCoord);

    if (startFrame.isValid_) {
        // build frames from left to right
        for (unsigned int i = 0; i < nRects; i++) {
            auto frame = startFrame;
            frame.rect_.left += i * frame.rect_.width;
            frames.push_back(frame);
        }
    }

    return frames;
}

}  // namespace Shared

}  // namespace FA
