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
    stateData_.configuration_->sprite_->Update(deltaTime);
    stateData_.configuration_->movement_->Update(deltaTime);
}

void MoveState::DrawTo(sf::RenderTarget& renderTarget)
{
    stateData_.configuration_->sprite_->DrawTo(renderTarget);
}

void MoveState::Enter()
{
    stateData_.configuration_->sprite_->Set(FrameType::Move, stateData_.configuration_->faceDir_);
}

void MoveState::Exit()
{
    stateData_.configuration_->movement_->SetDirection(MoveDirection::None);
}

void MoveState::OnStopMove()
{
    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
