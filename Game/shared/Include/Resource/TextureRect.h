/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "ResourceId.h"

namespace FA {

namespace Shared {

struct TextureRect
{
    TextureRect() = default;

    TextureRect(ResourceId id, const sf::Vector2i &position, const sf::Vector2i &size)
        : id_(id)
        , position_(position)
        , size_(size)
        , isValid_(true)
    {}

    ResourceId id_{};
    sf::Vector2i position_;
    sf::Vector2i size_;
    bool isValid_{false};
};

}  // namespace Shared

}  // namespace FA
