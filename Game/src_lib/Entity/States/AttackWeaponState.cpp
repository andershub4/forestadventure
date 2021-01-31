/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponState.h"

#include "Animation/Animation.h"
#include "IdleState.h"
#include "MoveState.h"

namespace FA {

namespace Entity {

AttackWeaponState::AttackWeaponState(StateMachine& stateMachine, const AnimationFactory& animationFactory,
                                     StateData& stateData)
    : BasicState(stateMachine, animationFactory, stateData)
{}

AttackWeaponState::~AttackWeaponState() = default;

void AttackWeaponState::Update(float deltaTime)
{
    if (animation_) {
        animation_->Update(deltaTime);
        if (animation_->IsCompleted()) {
            SwitchState<IdleState>();
        }
    }
}

void AttackWeaponState::Enter()
{
    animation_ = animationFactory_.Create(FrameType::AttackWeapon, stateData_.faceDir_, stateData_.rectShape_);
    animation_->Start();
}

void AttackWeaponState::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
