/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Entity/Components/Sprite/BasicSprite.h"
#include "IdleState.h"
#include "MoveState.h"

namespace FA {

namespace Entity {

AttackState::AttackState(StateMachine& stateMachine, BasicSprite& sprite, StateData& stateData)
    : BasicState(stateMachine, sprite, stateData)
{}

AttackState::~AttackState() = default;

void AttackState::Update(float deltaTime)
{
    sprite_.Update(deltaTime);
    if (sprite_.AnimationIsCompleted()) {
        SwitchState<IdleState>();
    }
}

void AttackState::Enter()
{
    sprite_.SetAnimation(FrameType::Attack, stateData_.faceDir_);
    sprite_.StartAnimation();
}

void AttackState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
