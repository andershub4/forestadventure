/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Animation/Animation.h"
#include "IdleState.h"
#include "MoveState.h"

namespace FA {

namespace Entity {

AttackState::AttackState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

AttackState::~AttackState() = default;

void AttackState::Update(float deltaTime)
{
    if (animation_) {
        animation_->Update(deltaTime);
        if (animation_->IsCompleted()) {
            SwitchState<IdleState>();
        }
    }
}

void AttackState::Enter()
{
    animation_ = stateData_.animationFactory_.Create(FrameType::Attack, stateData_.faceDir_, stateData_.rectShape_);
    animation_->Start();
}

void AttackState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
