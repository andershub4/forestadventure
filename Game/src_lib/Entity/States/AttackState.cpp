/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/SpriteAttribute.h"
#include "Entity/Behaviors/IdleBehavior.h"
#include "Entity/Behaviors/MovementBehavior.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

AttackState::AttackState(StateMachine& stateMachine, StateData& stateData, PropertyHandler& propertyHandler)
    : BasicState(stateMachine, stateData, propertyHandler)
{}

AttackState::~AttackState() = default;

void AttackState::Update(float deltaTime)
{
    GetAttribute<SpriteAttribute>()->Update(deltaTime);

    if (GetAttribute<SpriteAttribute>()->AnimationIsCompleted()) {
        GetBehavior<IdleBehavior>()->Execute(*this);
    }
}

void AttackState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetAttribute<SpriteAttribute>()->DrawTo(renderTarget);
}

void AttackState::Enter()
{
    GetAttribute<SpriteAttribute>()->Set(FrameType::Attack);
}

void AttackState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetBehavior<MovementBehavior>()->SetDirection(moveDir);
    GetAttribute<FaceDirectionAttribute>()->SetDirection(faceDir);
    GetBehavior<MovementBehavior>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
