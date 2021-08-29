/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "Entity/Components/MovementComponent.h"
#include "Entity/Components/SpriteComponent.h"
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
    stateData_.configuration_->GetComponent<SpriteComponent>()->Update(deltaTime);
    stateData_.configuration_->GetComponent<MovementComponent>()->Update(deltaTime);
}

void MoveState::DrawTo(sf::RenderTarget& renderTarget)
{
    stateData_.configuration_->GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void MoveState::Enter()
{
    stateData_.configuration_->GetComponent<SpriteComponent>()->Set(FrameType::Move,
                                                                    stateData_.configuration_->faceDir_);
}

void MoveState::Exit()
{
    stateData_.configuration_->GetComponent<MovementComponent>()->SetDirection(MoveDirection::None);
}

void MoveState::OnStopMove()
{
    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
