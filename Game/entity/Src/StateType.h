/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

namespace FA {

namespace Entity {

enum class StateType { None, Uninitialized, Idle, Move, Attack, AttackWeapon, Collision, Dead };

inline std::ostream& operator<<(std::ostream& os, const StateType& e)
{
    std::string str;
    switch (e) {
        case StateType::Uninitialized:
            str = "Uninitialized";
            break;
        case StateType::Attack:
            str = "Attack";
            break;
        case StateType::AttackWeapon:
            str = "AttackWeapon";
            break;
        case StateType::Idle:
            str = "Idle";
            break;
        case StateType::Move:
            str = "Move";
            break;
        case StateType::Collision:
            str = "Collision";
            break;
        case StateType::Dead:
            str = "Dead";
            break;
        case StateType::None:
            str = "None";
            break;
    }

    os << str;

    return os;
}

}  // namespace Entity

}  // namespace FA
