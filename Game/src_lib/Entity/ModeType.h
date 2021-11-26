/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

namespace FA {

namespace Entity {

enum class ModeType { None, Uninitialized, Idle, Move, Attack, AttackWeapon };

inline std::ostream& operator<<(std::ostream& os, const ModeType& e)
{
    std::string str;
    switch (e) {
        case ModeType::Uninitialized:
            str = "Uninitialized";
            break;
        case ModeType::Attack:
            str = "Attack";
            break;
        case ModeType::AttackWeapon:
            str = "AttackWeapon";
            break;
        case ModeType::Idle:
            str = "Idle";
            break;
        case ModeType::Move:
            str = "Move";
            break;
        case ModeType::None:
            str = "None";
            break;
    }

    os << str;

    return os;
}

}  // namespace Entity

}  // namespace FA
