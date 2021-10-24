/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Entity/Shapes/Shape.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

MoveState::MoveState(StateMachine& stateMachine, StateData& stateData, EntityService& propertyHandler)
    : BasicState(stateMachine, stateData, propertyHandler)
{}

MoveState::~MoveState() = default;

void MoveState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);
    GetMode<MoveMode>()->Update(deltaTime);
}

void MoveState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

void MoveState::Enter()
{
    GetShape()->Set(FrameType::Move);
}

void MoveState::Exit()
{
    GetMode<MoveMode>()->SetDirection(MoveDirection::None);
}

void MoveState::OnStopMove()
{
    GetMode<IdleMode>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
