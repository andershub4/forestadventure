/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SpriteSheet.h"

#include <SFML/Graphics/Texture.hpp>

#include "Logging.h"

namespace FA {

SpriteSheet::SpriteSheet(const sf::Texture* texture, const sf::Vector2u& rectCount)
    : texture_(texture)
    , rectCount_(rectCount)
    , isValid_(true)
{}

std::vector<sf::IntRect> SpriteSheet::MirrorX(const std::vector<sf::IntRect>& rects)
{
    std::vector<sf::IntRect> mirrorRects;
    for (const auto& rect : rects) {
        mirrorRects.emplace_back(rect.left + rect.width, rect.top, -rect.width, rect.height);
    }

    return mirrorRects;
}

SpriteSheet::FrameSeq SpriteSheet::Scan(const sf::Vector2u& uvCoord, unsigned int nRects,
                                        unsigned int defaultIndex) const
{
    auto rects = GenerateRects(uvCoord, nRects);
    return FrameSeq(texture_, defaultIndex, rects);
}

SpriteSheet::Frame SpriteSheet::At(const sf::Vector2u& uvCoord) const
{
    auto rectSize = CalcRectSize();

    if (rectSize.x > 0 && rectSize.y) {
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
        LOG_ERROR("Can't calculate rectSize due to rectCount.x, rectCount.y  ", rectCount_.x, rectCount_.y);

    return {};
}

std::vector<sf::IntRect> SpriteSheet::GenerateRects(const sf::Vector2u& uvCoord, unsigned int nRects) const
{
    std::vector<sf::IntRect> rects;
    auto startRect = At(uvCoord).rect_;

    // build frames from left to right
    for (unsigned int i = 0; i < nRects; i++) {
        auto rect = startRect;
        rect.left += i * rect.width;
        rects.push_back(rect);
    }

    return rects;
}

}  // namespace FA
