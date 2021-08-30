/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "AttackState.h"
#include "AttackWeaponState.h"
#include "Entity/Components/FaceDirectionComponent.h"
#include "Entity/Components/MovementComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Enum/FrameType.h"
#include "MoveState.h"

namespace FA {

namespace Entity {

IdleState::IdleState(StateMachine& stateMachine, StateData& stateData, ComponentHandler& componentHandler)
    : BasicState(stateMachine, stateData, componentHandler)
{}

IdleState::~IdleState() = default;

void IdleState::Update(float deltaTime)
{
    GetComponent<SpriteComponent>()->Update(deltaTime);
}

void IdleState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void IdleState::Enter()
{
    GetComponent<SpriteComponent>()->Set(FrameType::Idle);
}

void IdleState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetComponent<MovementComponent>()->SetDirection(moveDir);
    GetComponent<FaceDirectionComponent>()->SetDirection(faceDir);
    SwitchState<MoveState>();
}

void IdleState::OnAttack()
{
    SwitchState<AttackState>();
}

void IdleState::OnAttackWeapon()
{
    SwitchState<AttackWeaponState>();
}

}  // namespace Entity

}  // namespace FA
