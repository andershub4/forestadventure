/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "Entity/Components/FaceDirectionComponent.h"
#include "Entity/Components/IdleComponent.h"
#include "Entity/Components/MovementComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

AttackWeaponState::AttackWeaponState(StateMachine& stateMachine, StateData& stateData,
                                     ComponentHandler& componentHandler)
    : BasicState(stateMachine, stateData, componentHandler)
{}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    GetComponent<SpriteComponent>()->Update(deltaTime);
    if (GetComponent<SpriteComponent>()->AnimationIsCompleted()) {
        GetComponent<IdleComponent>()->Execute(*this);
    }
}

void AttackWeaponState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void AttackWeaponState::Enter()
{
    GetComponent<SpriteComponent>()->Set(FrameType::AttackWeapon);
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetComponent<MovementComponent>()->SetDirection(moveDir);
    GetComponent<FaceDirectionComponent>()->SetDirection(faceDir);
    GetComponent<MovementComponent>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
