/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponComponent.h"

#include "Entity/States/AttackWeaponState.h"

namespace FA {

namespace Entity {

void AttackWeaponComponent::Execute(BasicState &oldState)
{
    oldState.SwitchState<AttackWeaponState>();
}

}  // namespace Entity

}  // namespace FA
