/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PropertyManager.h"

#include <SFML/System/Vector2.hpp>

#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

namespace {

template <class T>
T ToValue(const std::string &value)
{
    return T();
}

template <>
FaceDirection ToValue(const std::string &valueStr)
{
    static std::unordered_map<std::string, FaceDirection> map = {{"Down", FaceDirection::Down},
                                                                 {"Up", FaceDirection::Up},
                                                                 {"Left", FaceDirection::Left},
                                                                 {"Right", FaceDirection::Right}};

    auto it = map.find(valueStr);
    if (it != map.end()) {
        return map.at(valueStr);
    }

    return FaceDirection::Undefined;
}

}  // namespace

PropertyManager::PropertyManager() = default;

void PropertyManager::ReadCommonProperty(const std::string &name, const std::string &valueStr)
{
    sf::Vector2f pos;

    if (name == "X") {
        pos.x = ToValue<float>(valueStr);
    }
    else if (name == "Y") {
        pos.y = ToValue<float>(valueStr);
    }

    propertyStore_.Set<sf::Vector2f>("Position", pos);
}

void PropertyManager::ReadCustomProperty(const std::string &name, const std::string &valueStr)
{
    if (name == "FaceDirection") {
        auto v = ToValue<FaceDirection>(valueStr);
        propertyStore_.Set<FaceDirection>(name, v);
    }
}

}  // namespace Entity

}  // namespace FA
