/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/ShapeAttribute.h"
#include "Entity/Behaviors/AttackBehavior.h"
#include "Entity/Behaviors/AttackWeaponBehavior.h"
#include "Entity/Behaviors/MovementBehavior.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

IdleState::IdleState(StateMachine& stateMachine, StateData& stateData, PropertyHandler& propertyHandler)
    : BasicState(stateMachine, stateData, propertyHandler)
{}

IdleState::~IdleState() = default;

void IdleState::Update(float deltaTime)
{
    GetAttribute<ShapeAttribute>()->Update(deltaTime);
}

void IdleState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetAttribute<ShapeAttribute>()->DrawTo(renderTarget);
}

void IdleState::Enter()
{
    GetAttribute<ShapeAttribute>()->Set(FrameType::Idle);
}

void IdleState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetBehavior<MovementBehavior>()->SetDirection(moveDir);
    GetAttribute<FaceDirectionAttribute>()->SetDirection(faceDir);
    GetBehavior<MovementBehavior>()->Execute(*this);
}

void IdleState::OnAttack()
{
    GetBehavior<AttackBehavior>()->Execute(*this);
}

void IdleState::OnAttackWeapon()
{
    GetBehavior<AttackWeaponBehavior>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
