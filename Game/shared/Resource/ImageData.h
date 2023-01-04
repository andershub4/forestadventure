/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

namespace FA {

struct ImageData
{
    std::string sheetId_;
    sf::Vector2u position_;
};

}  // namespace FA
