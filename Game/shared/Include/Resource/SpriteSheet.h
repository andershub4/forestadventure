/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "ResourceId.h"
#include "SpriteSheetIf.h"
#include "TextureRect.h"

namespace FA {

namespace Shared {

class SpriteSheet : public SpriteSheetIf
{
public:
    SpriteSheet() = default;
    SpriteSheet(ResourceId textureId, const sf::Vector2u& textureSize, const sf::Vector2u& rectCount);

    virtual TextureRect At(const sf::Vector2u& uvCoord) const override;

private:
    ResourceId textureId_;
    sf::Vector2u textureSize_;
    sf::Vector2u rectCount_;
    bool isValid_ = false;
    sf::Vector2u rectSize_;
};

}  // namespace Shared

}  // namespace FA
