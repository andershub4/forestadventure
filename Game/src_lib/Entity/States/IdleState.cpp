/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "Entity/Components/AttackComponent.h"
#include "Entity/Components/AttackWeaponComponent.h"
#include "Entity/Components/FaceDirectionComponent.h"
#include "Entity/Components/MovementComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

IdleState::IdleState(StateMachine& stateMachine, StateData& stateData, ComponentHandler& componentHandler)
    : BasicState(stateMachine, stateData, componentHandler)
{}

IdleState::~IdleState() = default;

void IdleState::Update(float deltaTime)
{
    GetComponent<SpriteComponent>()->Update(deltaTime);
}

void IdleState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void IdleState::Enter()
{
    GetComponent<SpriteComponent>()->Set(FrameType::Idle);
}

void IdleState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetComponent<MovementComponent>()->SetDirection(moveDir);
    GetComponent<FaceDirectionComponent>()->SetDirection(faceDir);
    GetComponent<MovementComponent>()->Execute(*this);
}

void IdleState::OnAttack()
{
    GetComponent<AttackComponent>()->Execute(*this);
}

void IdleState::OnAttackWeapon()
{
    GetComponent<AttackWeaponComponent>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
