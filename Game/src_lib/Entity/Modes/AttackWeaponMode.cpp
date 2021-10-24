/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponMode.h"

#include "Entity/States/AttackWeaponState.h"

namespace FA {

namespace Entity {

AttackWeaponMode::AttackWeaponMode(EntityService *owner)
    : BasicMode(owner)
{}

void AttackWeaponMode::Execute(BasicState &oldState)
{
    oldState.SwitchState<AttackWeaponState>();
}

}  // namespace Entity

}  // namespace FA
