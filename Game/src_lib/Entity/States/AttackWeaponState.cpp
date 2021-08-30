/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "Entity/Components/MovementComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Enum/FrameType.h"
#include "IdleState.h"
#include "MoveState.h"

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
        SwitchState<IdleState>();
    }
}

void AttackWeaponState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void AttackWeaponState::Enter()
{
    GetComponent<SpriteComponent>()->Set(FrameType::AttackWeapon, GetFaceDir());
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    GetComponent<MovementComponent>()->SetDirection(moveDir);
    SetFaceDir(faceDir);
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
