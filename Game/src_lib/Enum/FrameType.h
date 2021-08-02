/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

namespace FA {

enum class FrameType { Undefined, Idle, Move, Attack, AttackWeapon };

inline std::ostream& operator<<(std::ostream& os, const FrameType& e)
{
    std::string str;
    switch (e) {
        case FrameType::Undefined:
            str = "Undefined";
            break;
        case FrameType::Idle:
            str = "Idle";
            break;
        case FrameType::Move:
            str = "Move";
            break;
        case FrameType::Attack:
            str = "Attack";
            break;
        case FrameType::AttackWeapon:
            str = "AttackWeapon";
            break;
    }

    os << str;

    return os;
}

}  // namespace FA
