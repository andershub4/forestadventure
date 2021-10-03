/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponBehavior.h"

#include "Entity/States/AttackWeaponState.h"

namespace FA {

namespace Entity {

AttackWeaponBehavior::AttackWeaponBehavior(PropertyHandler *owner)
    : BasicBehavior(owner)
{}

void AttackWeaponBehavior::Execute(BasicState &oldState)
{
    oldState.SwitchState<AttackWeaponState>();
}

}  // namespace Entity

}  // namespace FA
