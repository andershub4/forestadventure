/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "Animation/Animation.h"
#include "IdleState.h"

namespace FA {

namespace Entity {

MoveState::MoveState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
    , movement_(stateData_.rectShape_, stateData_.velocity_)
{}

MoveState::~MoveState() = default;

void MoveState::Update(float deltaTime)
{
    if (animation_) animation_->Update(deltaTime);
    movement_.Update(deltaTime);
}

void MoveState::Enter()
{
    movement_.SetDirection(stateData_.moveDir_);
    animation_ = stateData_.animationFactory_.Create(FrameType::Move, stateData_.faceDir_, stateData_.rectShape_);
    animation_->Start();
}

void MoveState::Exit()
{
    movement_.SetDirection(MoveDirection::None);
}

void MoveState::OnStopMove()
{
    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
