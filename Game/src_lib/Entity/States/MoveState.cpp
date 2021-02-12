/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "IdleState.h"
#include "Sprite/BasicSprite.h"

namespace FA {

namespace Entity {

MoveState::MoveState(StateMachine& stateMachine, BasicSprite& sprite, StateData& stateData)
    : BasicState(stateMachine, sprite, stateData)
    , movement_(stateData_.velocity_)
{}

MoveState::~MoveState() = default;

void MoveState::Update(float deltaTime)
{
    sprite_.Update(deltaTime);
    movement_.Update(deltaTime);
    sprite_.Move(movement_);
}

void MoveState::Enter()
{
    movement_.SetDirection(stateData_.moveDir_);
    sprite_.SetAnimation(FrameType::Move, stateData_.faceDir_);
    sprite_.StartAnimation();
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
