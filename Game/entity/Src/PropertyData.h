/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <unordered_map>

#include <SFML/System/Vector2.hpp>

#include "Resource/TileGraphic.h"

namespace FA {

namespace Entity {

struct PropertyData
{
    std::string typeStr_{};
    sf::Vector2f position_{};
    std::unordered_map<std::string, std::string> properties_;
    Shared::TileGraphic graphic_;
};

}  // namespace Entity

}  // namespace FA
