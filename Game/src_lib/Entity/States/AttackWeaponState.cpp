/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "IdleState.h"
#include "MoveState.h"
#include "Sprite/BasicSprite.h"

namespace FA {

namespace Entity {

AttackWeaponState::AttackWeaponState(StateMachine& stateMachine, BasicSprite& sprite, StateData& stateData)
    : BasicState(stateMachine, sprite, stateData)
{}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    sprite_.Update(deltaTime);
    if (sprite_.AnimationIsCompleted()) {
        SwitchState<IdleState>();
    }
}

void AttackWeaponState::Enter()
{
    sprite_.SetAnimation(FrameType::AttackWeapon, stateData_.faceDir_);
    sprite_.StartAnimation();
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
