/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityStateIdle.h"

#include "Animation/Animation.h"
#include "EntityStateAttack.h"
#include "EntityStateMove.h"

namespace FA {

EntityStateIdle::EntityStateIdle(EntityStateMachine& stateMachine, StateData& stateData)
    : EntityState(stateMachine, stateData)
{}

EntityStateIdle::~EntityStateIdle() = default;

void EntityStateIdle::Update(float deltaTime)
{
    if (animation_) animation_->Update(deltaTime);
}

void EntityStateIdle::Enter()
{
    animation_ = stateData_.animationFactory_.Create(FrameType::Idle, stateData_.faceDir_, stateData_.rectShape_);
}

void EntityStateIdle::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<EntityStateMove>();
}

void EntityStateIdle::OnStartAttack()
{
    SwitchState<EntityStateAttack>();
}

}  // namespace FA
