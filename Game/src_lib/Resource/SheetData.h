/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

namespace FA {

struct SheetData
{
    std::string name_;
    std::string path_;
    sf::Vector2u size_;
};

}  // namespace FA
