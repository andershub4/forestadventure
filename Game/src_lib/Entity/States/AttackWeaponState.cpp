/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Behaviors/IdleBehavior.h"
#include "Entity/Behaviors/MovementBehavior.h"
#include "Entity/Shape.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

AttackWeaponState::AttackWeaponState(StateMachine& stateMachine, StateData& stateData, EntityService& entityService)
    : BasicState(stateMachine, stateData, entityService)
{}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);
    if (GetShape()->AnimationIsCompleted()) {
        GetBehavior<IdleBehavior>()->Execute(*this);
    }
}

void AttackWeaponState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

void AttackWeaponState::Enter()
{
    GetShape()->Set(FrameType::AttackWeapon);
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetBehavior<MovementBehavior>()->SetDirection(moveDir);
    GetAttribute<FaceDirectionAttribute>()->SetDirection(faceDir);
    GetBehavior<MovementBehavior>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
