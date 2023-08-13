/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Resource/SpriteSheet.h"

#include "Logging.h"

namespace FA {

namespace Shared {

SpriteSheet::SpriteSheet(ResourceId textureId, const sf::Vector2u& textureSize, const sf::Vector2u& rectCount)
    : textureId_(textureId)
    , textureSize_(textureSize)
    , rectCount_(rectCount)
    , isValid_(true)
{}

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
    auto rectSize = CalcRectSize();

    if (rectSize.x > 0 && rectSize.y > 0) {
        int left = static_cast<int>(uvCoord.x * rectSize.x);
        int top = static_cast<int>(uvCoord.y * rectSize.y);
        int width = static_cast<int>(rectSize.x);
        int height = static_cast<int>(rectSize.y);
        return TextureRect(textureId_, {left, top}, {width, height});
    }

    return {};
}

sf::Vector2u SpriteSheet::CalcRectSize() const
{
    if (rectCount_.x > 0 && rectCount_.y > 0)
        return {textureSize_.x / rectCount_.x, textureSize_.y / rectCount_.y};
    else
        LOG_ERROR("Can't calculate rectSize due to rectCount.x %u, rectCount.y  %u", rectCount_.x, rectCount_.y);

    return {};
}

std::vector<TextureRect> SpriteSheet::GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nRects) const
{
    std::vector<TextureRect> rects;
    auto startRect = At(uvCoord);

    if (startRect.isValid_) {
        // build frames from left to right
        for (unsigned int i = 0; i < nRects; i++) {
            auto rect = startRect;
            rect.position_.x += i * rect.size_.x;
            rects.push_back(rect);
        }
    }

    return rects;
}

}  // namespace Shared

}  // namespace FA
