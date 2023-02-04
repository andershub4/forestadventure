/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PropertyConverter.h"

#include <unordered_map>

namespace FA {

namespace Entity {

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

template <>
MoveDirection ToValue(const std::string &valueStr)
{
    static std::unordered_map<std::string, MoveDirection> map = {{"Down", MoveDirection::Down},
                                                                 {"Up", MoveDirection::Up},
                                                                 {"Left", MoveDirection::Left},
                                                                 {"Right", MoveDirection::Right}};

    auto it = map.find(valueStr);
    if (it != map.end()) {
        return map.at(valueStr);
    }

    return MoveDirection::None;
}

}  // namespace Entity

}  // namespace FA
