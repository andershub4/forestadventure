/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "AttackState.h"
#include "AttackWeaponState.h"
#include "MoveState.h"
#include "Sprite/BasicSprite.h"

namespace FA {

namespace Entity {

IdleState::IdleState(StateMachine& stateMachine, BasicSprite& sprite, StateData& stateData)
    : BasicState(stateMachine, sprite, stateData)
{}

IdleState::~IdleState() = default;

void IdleState::Update(float deltaTime)
{
    sprite_.Update(deltaTime);
}

void IdleState::Enter()
{
    sprite_.SetAnimation(FrameType::Idle, stateData_.faceDir_);
    sprite_.StartAnimation();
}

void IdleState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
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
