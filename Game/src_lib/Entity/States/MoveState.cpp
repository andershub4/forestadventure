/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "Entity/Attributes/SpriteAttribute.h"
#include "Entity/Behaviors/IdleBehavior.h"
#include "Entity/Behaviors/MovementBehavior.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

MoveState::MoveState(StateMachine& stateMachine, StateData& stateData, PropertyHandler& propertyHandler)
    : BasicState(stateMachine, stateData, propertyHandler)
{}

MoveState::~MoveState() = default;

void MoveState::Update(float deltaTime)
{
    GetAttribute<SpriteAttribute>()->Update(deltaTime);
    GetBehavior<MovementBehavior>()->Update(deltaTime);
}

void MoveState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetAttribute<SpriteAttribute>()->DrawTo(renderTarget);
}

void MoveState::Enter()
{
    GetAttribute<SpriteAttribute>()->Set(FrameType::Move);
}

void MoveState::Exit()
{
    GetBehavior<MovementBehavior>()->SetDirection(MoveDirection::None);
}

void MoveState::OnStopMove()
{
    GetBehavior<IdleBehavior>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
