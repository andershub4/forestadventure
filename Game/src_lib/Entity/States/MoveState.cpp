/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "Entity/Components/IdleComponent.h"
#include "Entity/Components/MovementComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

MoveState::MoveState(StateMachine& stateMachine, StateData& stateData, ComponentHandler& componentHandler)
    : BasicState(stateMachine, stateData, componentHandler)
{}

MoveState::~MoveState() = default;

void MoveState::Update(float deltaTime)
{
    GetComponent<SpriteComponent>()->Update(deltaTime);
    GetComponent<MovementComponent>()->Update(deltaTime);
}

void MoveState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void MoveState::Enter()
{
    GetComponent<SpriteComponent>()->Set(FrameType::Move);
}

void MoveState::Exit()
{
    GetComponent<MovementComponent>()->SetDirection(MoveDirection::None);
}

void MoveState::OnStopMove()
{
    GetComponent<IdleComponent>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
