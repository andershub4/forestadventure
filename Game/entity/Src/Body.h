/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

namespace FA {

namespace Entity {

struct Body
{
    sf::Vector2f position_;
    sf::Vector2f prevPosition_;
    float rotation_{};
    float scale_{};
};

}  // namespace Entity

}  // namespace FA
