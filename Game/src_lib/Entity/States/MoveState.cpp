/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "Entity/Components/Sprite/SpriteComponent.h"
#include "Enum/FrameType.h"
#include "IdleState.h"

namespace FA {

namespace Entity {

MoveState::MoveState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

MoveState::~MoveState() = default;

void MoveState::Update(float deltaTime)
{
    stateData_.sprite_.Update(deltaTime);
    stateData_.movement_.Update(deltaTime);
    stateData_.movement_.ApplyTo(stateData_.transform_);
}

void MoveState::LateUpdate()
{
    stateData_.sprite_.Apply(stateData_.transform_);
}

void MoveState::DrawTo(sf::RenderTarget& renderTarget)
{
    stateData_.sprite_.DrawTo(renderTarget);
}

void MoveState::Enter()
{
    stateData_.sprite_.Set(FrameType::Move, stateData_.faceDir_);
}

void MoveState::Exit()
{
    stateData_.movement_.SetDirection(MoveDirection::None);
}

void MoveState::OnStopMove()
{
    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
