/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <SFML/Graphics/Rect.hpp>

#include "Resource/SpriteSheet.h"

#include "Logging.h"

namespace FA {

namespace Shared {

SpriteSheet::SpriteSheet(ResourceId textureId, const sf::Vector2u& textureSize, const sf::Vector2u& rectCount)
    : textureId_(textureId)
    , textureSize_(textureSize)
    , rectCount_(rectCount)
    , isValid_(true)
{
    if (rectCount_.x == 0 || rectCount_.y == 0 || textureSize_.x == 0 || textureSize_.y == 0) {
        isValid_ = false;
    }
    else {
        rectSize_ = {textureSize_.x / rectCount_.x, textureSize_.y / rectCount_.y};
        isValid_ = rectSize_.x > 0 && rectSize_.y > 0;
    }
}

std::vector<TextureRect> SpriteSheet::MirrorX(const std::vector<TextureRect>& rects)
{
    std::vector<TextureRect> mirrorRects;

    for (const auto& rect : rects) {
        TextureRect r = rect;
        r.position_.x = r.position_.x + r.size_.x;
        r.size_.x = -rect.size_.x;
        mirrorRects.push_back(r);
    }

    return mirrorRects;
}

std::vector<TextureRect> SpriteSheet::Scan(const sf::Vector2u& uvCoord, unsigned int nRects) const
{
    return GenerateFrames(uvCoord, nRects);
}

TextureRect SpriteSheet::At(const sf::Vector2u& uvCoord) const
{
    if (isValid_) {
        sf::IntRect r(0, 0, rectCount_.x, rectCount_.y);
        bool validCoord = r.contains(static_cast<sf::Vector2i>(uvCoord));
        if (!validCoord) {
            LOG_ERROR("%s is outside sheet boundary %s", DUMP(uvCoord), DUMP(rectCount_));
            return {};
        }

        int left = static_cast<int>(uvCoord.x * rectSize_.x);
        int top = static_cast<int>(uvCoord.y * rectSize_.y);
        int width = static_cast<int>(rectSize_.x);
        int height = static_cast<int>(rectSize_.y);
        return TextureRect(textureId_, {left, top}, {width, height});
    }

    LOG_ERROR("Invalid sheet %s %s", DUMP(textureSize_), DUMP(rectCount_));
    return {};
}

std::vector<TextureRect> SpriteSheet::GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nRects) const
{
    std::vector<TextureRect> rects;
    auto startRect = At(uvCoord);

    if (startRect.isValid_) {
        unsigned int n = nRects;
        unsigned int maxRange = rectCount_.x - uvCoord.x;
        if (nRects > maxRange) {
            n = maxRange;
            LOG_ERROR("Scan is outside sheet boundary %s with %s and %s", DUMP(rectCount_), DUMP(uvCoord),
                      DUMP(nRects));
        }
        // build frames from left to right
        for (unsigned int i = 0; i < n; i++) {
            auto rect = startRect;
            rect.position_.x += i * rect.size_.x;
            rects.push_back(rect);
        }
    }

    return rects;
}

}  // namespace Shared

}  // namespace FA
