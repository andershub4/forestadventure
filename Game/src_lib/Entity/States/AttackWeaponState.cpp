/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

AttackWeaponState::AttackWeaponState(StateController& stateController, StateData& stateData,
                                     EntityService& entityService, std::shared_ptr<BasicEvent> event)
    : BasicState(stateController, stateData, entityService)
{
    InternalEnter(event);
}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);
    BasicState::Update();
}

void AttackWeaponState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

}  // namespace Entity

}  // namespace FA
