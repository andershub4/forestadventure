/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityStateAttack.h"

#include "Animation/Animation.h"
#include "EntityStateIdle.h"
#include "EntityStateMove.h"

namespace FA {

EntityStateAttack::EntityStateAttack(EntityStateMachine& stateMachine, StateData& stateData)
    : EntityState(stateMachine, stateData)
{}

EntityStateAttack::~EntityStateAttack() = default;

void EntityStateAttack::Update(float deltaTime)
{
    if (animation_) {
        animation_->Update(deltaTime);
        if (animation_->IsCompleted()) {
            SwitchState<EntityStateIdle>();
        }
    }
}

void EntityStateAttack::Enter()
{
    animation_ = stateData_.animationFactory_.Create(FrameType::Attack, stateData_.faceDir_, stateData_.rectShape_);
    animation_->Start();
}

void EntityStateAttack::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<EntityStateMove>();
}

}  // namespace FA
