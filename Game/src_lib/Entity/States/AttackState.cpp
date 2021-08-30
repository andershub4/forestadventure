/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Entity/Components/FaceDirectionComponent.h"
#include "Entity/Components/MovementComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Enum/FrameType.h"
#include "IdleState.h"
#include "MoveState.h"

namespace FA {

namespace Entity {

AttackState::AttackState(StateMachine& stateMachine, StateData& stateData, ComponentHandler& componentHandler)
    : BasicState(stateMachine, stateData, componentHandler)
{}

AttackState::~AttackState() = default;

void AttackState::Update(float deltaTime)
{
    GetComponent<SpriteComponent>()->Update(deltaTime);

    if (GetComponent<SpriteComponent>()->AnimationIsCompleted()) {
        SwitchState<IdleState>();
    }
}

void AttackState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void AttackState::Enter()
{
    GetComponent<SpriteComponent>()->Set(FrameType::Attack);
}

void AttackState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetComponent<MovementComponent>()->SetDirection(moveDir);
    GetComponent<FaceDirectionComponent>()->SetDirection(faceDir);
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
