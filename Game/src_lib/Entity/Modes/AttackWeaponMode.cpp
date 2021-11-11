/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponMode.h"

#include "Entity/EntityService.h"
#include "Entity/Shapes/Shape.h"
#include "Entity/StateController.h"
#include "Entity/States/AttackWeaponState.h"

namespace FA {

namespace Entity {

AttackWeaponMode::AttackWeaponMode(EntityService *owner)
    : BasicMode(owner)
{}

void AttackWeaponMode::Enter(std::shared_ptr<BasicEvent> event)
{
    Owner()->GetShape()->Set(FrameType::AttackWeapon);
}

std::unique_ptr<BasicState> AttackWeaponMode::CreateState(StateController &stateController,
                                                          std::shared_ptr<BasicEvent> event) const
{
    return stateController.CreateState<AttackWeaponState>(event);
}

}  // namespace Entity

}  // namespace FA
