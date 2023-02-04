/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

namespace FA {

enum class MoveDirection { None, Up, Right, Down, Left };

inline std::ostream& operator<<(std::ostream& os, const MoveDirection& e)
{
    std::string str;
    switch (e) {
        case MoveDirection::None:
            str = "Undefined";
            break;
        case MoveDirection::Up:
            str = "Up";
            break;
        case MoveDirection::Right:
            str = "Right";
            break;
        case MoveDirection::Down:
            str = "Down";
            break;
        case MoveDirection::Left:
            str = "Left";
            break;
    }

    os << str;

    return os;
}

}  // namespace FA
