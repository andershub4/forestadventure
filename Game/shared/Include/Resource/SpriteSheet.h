/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "ResourceId.h"
#include "TextureRect.h"

namespace FA {

namespace Shared {

class SpriteSheet
{
public:
    SpriteSheet() = default;
    SpriteSheet(ResourceId textureId, const sf::Vector2u& textureSize, const sf::Vector2u& rectCount);

    bool IsValid() const { return isValid_; }
    std::vector<TextureRect> Scan(const sf::Vector2u& uvCoord, unsigned int nRects) const;
    TextureRect At(const sf::Vector2u& uvCoord) const;

private:
    ResourceId textureId_;
    sf::Vector2u textureSize_;
    sf::Vector2u rectCount_;
    bool isValid_ = false;
    sf::Vector2u rectSize_;

private:
    std::vector<TextureRect> GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nRects) const;
};

}  // namespace Shared

}  // namespace FA
