/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <unordered_map>

#include <SFML/System/Vector2.hpp>

namespace FA {

namespace Shared {

struct EntityData
{
    std::string typeStr_{};
    sf::Vector2f position_{};
    sf::Vector2f size_{};
    std::unordered_map<std::string, std::string> properties_;
};

}  // namespace Shared

}  // namespace FA
