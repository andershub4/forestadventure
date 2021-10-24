/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MovementMode.h"
#include "Entity/Shapes/Shape.h"
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
        GetMode<IdleMode>()->Execute(*this);
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
    GetMode<MovementMode>()->SetDirection(moveDir);
    GetAttribute<FaceDirectionAttribute>()->SetDirection(faceDir);
    GetMode<MovementMode>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
