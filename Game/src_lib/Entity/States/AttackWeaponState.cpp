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

AttackWeaponState::AttackWeaponState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    stateData_.configuration_->GetComponent<SpriteComponent>()->Update(deltaTime);
    if (stateData_.configuration_->GetComponent<SpriteComponent>()->AnimationIsCompleted()) {
        SwitchState<IdleState>();
    }
}

void AttackWeaponState::DrawTo(sf::RenderTarget& renderTarget)
{
    stateData_.configuration_->GetComponent<SpriteComponent>()->DrawTo(renderTarget);
}

void AttackWeaponState::Enter()
{
    stateData_.configuration_->GetComponent<SpriteComponent>()->Set(FrameType::AttackWeapon,
                                                                    stateData_.configuration_->faceDir_);
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.configuration_->GetComponent<MovementComponent>()->SetDirection(moveDir);
    stateData_.configuration_->faceDir_ = faceDir;
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
