/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "Entity/Components/Sprite/SpriteComponent.h"
#include "Enum/FrameType.h"
#include "IdleState.h"
#include "MoveState.h"

namespace FA {

namespace Entity {

AttackWeaponState::AttackWeaponState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    stateData_.sprite_.Update(deltaTime);
    if (stateData_.sprite_.AnimationIsCompleted()) {
        SwitchState<IdleState>();
    }
}

void AttackWeaponState::DrawTo(sf::RenderTarget& renderTarget)
{
    stateData_.sprite_.DrawTo(renderTarget);
}

void AttackWeaponState::Enter()
{
    stateData_.sprite_.Set(FrameType::AttackWeapon, stateData_.faceDir_);
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
