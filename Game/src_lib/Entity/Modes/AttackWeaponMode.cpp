/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponMode.h"

#include "Entity/EntityService.h"
#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

AttackWeaponMode::AttackWeaponMode(EntityService &entityService)
    : BasicMode(entityService)
{}

void AttackWeaponMode::Enter(std::shared_ptr<BasicEvent> event)
{
    Service().GetShape()->Set(FrameType::AttackWeapon);
}

void AttackWeaponMode::Update(float deltaTime)
{
    Service().GetShape()->Update(deltaTime);
}

}  // namespace Entity

}  // namespace FA
