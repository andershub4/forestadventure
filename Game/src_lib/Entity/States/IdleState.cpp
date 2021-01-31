/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "Animation/Animation.h"
#include "AttackState.h"
#include "AttackWeaponState.h"
#include "MoveState.h"

namespace FA {

namespace Entity {

IdleState::IdleState(StateMachine& stateMachine, const AnimationFactory& animationFactory, StateData& stateData)
    : BasicState(stateMachine, animationFactory, stateData)
{}

IdleState::~IdleState() = default;

void IdleState::Update(float deltaTime)
{
    if (animation_) animation_->Update(deltaTime);
}

void IdleState::Enter()
{
    animation_ = animationFactory_.Create(FrameType::Idle, stateData_.faceDir_, stateData_.rectShape_);
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
