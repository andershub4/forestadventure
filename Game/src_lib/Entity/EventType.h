/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

namespace FA {

namespace Entity {

enum class EventType { None, Create, Destroy, Init, StartMove, StopMove, Attack, AttackWeapon, Collision };

inline std::ostream& operator<<(std::ostream& os, const EventType& e)
{
    std::string str;
    switch (e) {
        case EventType::Attack:
            str = "Attack";
            break;
        case EventType::AttackWeapon:
            str = "AttackWeapon";
            break;
        case EventType::Collision:
            str = "Collision";
            break;
        case EventType::Create:
            str = "Create";
            break;
        case EventType::Destroy:
            str = "Destroy";
            break;
        case EventType::Init:
            str = "Init";
            break;
        case EventType::None:
            str = "None";
            break;
        case EventType::StartMove:
            str = "StartMove";
            break;
        case EventType::StopMove:
            str = "StopMove";
            break;
    }

    os << str;

    return os;
}

}  // namespace Entity

}  // namespace FA
