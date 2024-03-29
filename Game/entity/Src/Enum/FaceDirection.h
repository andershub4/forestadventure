/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

namespace FA {

namespace Entity {

enum class FaceDirection { Undefined, Up, Right, Down, Left };

inline std::ostream& operator<<(std::ostream& os, const FaceDirection& e)
{
    std::string str;
    switch (e) {
        case FaceDirection::Undefined:
            str = "Undefined";
            break;
        case FaceDirection::Up:
            str = "Up";
            break;
        case FaceDirection::Right:
            str = "Right";
            break;
        case FaceDirection::Down:
            str = "Down";
            break;
        case FaceDirection::Left:
            str = "Left";
            break;
    }

    os << str;

    return os;
}

}  // namespace Entity

}  // namespace FA
