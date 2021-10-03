/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/SpriteAttribute.h"
#include "Entity/Behaviors/IdleBehavior.h"
#include "Entity/Behaviors/MovementBehavior.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

AttackWeaponState::AttackWeaponState(StateMachine& stateMachine, StateData& stateData, PropertyHandler& propertyHandler)
    : BasicState(stateMachine, stateData, propertyHandler)
{}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    GetAttribute<SpriteAttribute>()->Update(deltaTime);
    if (GetAttribute<SpriteAttribute>()->AnimationIsCompleted()) {
        GetBehavior<IdleBehavior>()->Execute(*this);
    }
}

void AttackWeaponState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetAttribute<SpriteAttribute>()->DrawTo(renderTarget);
}

void AttackWeaponState::Enter()
{
    GetAttribute<SpriteAttribute>()->Set(FrameType::AttackWeapon);
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetBehavior<MovementBehavior>()->SetDirection(moveDir);
    GetAttribute<FaceDirectionAttribute>()->SetDirection(faceDir);
    GetBehavior<MovementBehavior>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
