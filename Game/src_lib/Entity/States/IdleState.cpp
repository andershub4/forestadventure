/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "Entity/Modes/AttackMode.h"
#include "Entity/Modes/AttackWeaponMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Entity/Shapes/Shape.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

IdleState::IdleState(StateMachine& stateMachine, StateData& stateData, EntityService& entityService)
    : BasicState(stateMachine, stateData, entityService)
{}

IdleState::~IdleState() = default;

void IdleState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);
}

void IdleState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

void IdleState::Enter()
{
    GetShape()->Set(FrameType::Idle);
}

void IdleState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetMode<MoveMode>()->SetDirection(moveDir, faceDir);
    GetMode<MoveMode>()->Execute(*this);
}

void IdleState::OnAttack()
{
    GetMode<AttackMode>()->Execute(*this);
}

void IdleState::OnAttackWeapon()
{
    GetMode<AttackWeaponMode>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
