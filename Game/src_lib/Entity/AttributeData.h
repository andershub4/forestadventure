/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Resource/Frame.h"

namespace FA {

namespace Entity {

struct AttributeData
{
    sf::Vector2f position_{};
    std::unordered_map<std::string, std::string> properties_;
    float scale_{};
    std::vector<Frame> frames_;
    Frame frame_;
};

}  // namespace Entity

}  // namespace FA
