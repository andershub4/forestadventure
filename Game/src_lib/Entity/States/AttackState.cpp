/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Behaviors/IdleBehavior.h"
#include "Entity/Behaviors/MovementBehavior.h"
#include "Entity/Shape.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

AttackState::AttackState(StateMachine& stateMachine, StateData& stateData, EntityService& entityService)
    : BasicState(stateMachine, stateData, entityService)
{}

AttackState::~AttackState() = default;

void AttackState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);

    if (GetShape()->AnimationIsCompleted()) {
        GetBehavior<IdleBehavior>()->Execute(*this);
    }
}

void AttackState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

void AttackState::Enter()
{
    GetShape()->Set(FrameType::Attack);
}

void AttackState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetBehavior<MovementBehavior>()->SetDirection(moveDir);
    GetAttribute<FaceDirectionAttribute>()->SetDirection(faceDir);
    GetBehavior<MovementBehavior>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
