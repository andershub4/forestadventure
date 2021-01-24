/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityStateAttackWeapon.h"

#include "Animation/Animation.h"
#include "EntityStateIdle.h"
#include "EntityStateMove.h"

namespace FA {

EntityStateAttackWeapon::EntityStateAttackWeapon(EntityStateMachine& stateMachine, StateData& stateData)
    : EntityState(stateMachine, stateData)
{}

EntityStateAttackWeapon::~EntityStateAttackWeapon() = default;

void EntityStateAttackWeapon::Update(float deltaTime)
{
    if (animation_) {
        animation_->Update(deltaTime);
        if (animation_->IsCompleted()) {
            SwitchState<EntityStateIdle>();
        }
    }
}

void EntityStateAttackWeapon::Enter()
{
    animation_ =
        stateData_.animationFactory_.Create(FrameType::AttackWeapon, stateData_.faceDir_, stateData_.rectShape_);
    animation_->Start();
}

void EntityStateAttackWeapon::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<EntityStateMove>();
}

}  // namespace FA
