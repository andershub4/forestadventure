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

}  // namespace Shared

}  // namespace FA
