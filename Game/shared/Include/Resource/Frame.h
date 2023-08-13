/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "SfmlFwd.h"

namespace FA {

namespace Shared {

struct Frame
{
    const sf::Texture *texture_ = nullptr;
    sf::IntRect rect_;
};

}  // namespace Shared

}  // namespace FA
