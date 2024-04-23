/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "SfmlFwd.h"

#include "ResourceId.h"
#include "TextureRect.h"

namespace FA {

namespace Shared {

class SpriteSheetIf
{
public:
    virtual ~SpriteSheetIf() = default;
    virtual TextureRect At(const sf::Vector2u& uvCoord) const = 0;
};

}  // namespace Shared

}  // namespace FA
