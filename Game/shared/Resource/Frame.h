/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

struct Frame
{
    Frame(const sf::Texture* texture, const sf::IntRect& rect)
        : texture_(texture)
        , rect_(rect)
        , isValid_(true)
    {}

    Frame() = default;

    const sf::Texture* texture_ = nullptr;
    sf::IntRect rect_;
    bool isValid_ = false;
};

}  // namespace FA
