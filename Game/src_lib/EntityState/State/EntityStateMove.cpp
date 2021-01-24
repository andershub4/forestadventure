/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityStateMove.h"

#include "Animation/Animation.h"
#include "EntityStateIdle.h"

namespace FA {

EntityStateMove::EntityStateMove(EntityStateMachine& stateMachine, StateData& stateData)
    : EntityState(stateMachine, stateData)
    , movement_(stateData_.rectShape_, stateData_.velocity_)
{}

EntityStateMove::~EntityStateMove() = default;

void EntityStateMove::Update(float deltaTime)
{
    if (animation_) animation_->Update(deltaTime);
    movement_.Update(deltaTime);
}

void EntityStateMove::Enter()
{
    movement_.SetDirection(stateData_.moveDir_);
    animation_ = stateData_.animationFactory_.Create(FrameType::Move, stateData_.faceDir_, stateData_.rectShape_);
    animation_->Start();
}

void EntityStateMove::Exit()
{
    movement_.SetDirection(MoveDirection::None);
}

void EntityStateMove::OnStopMove()
{
    SwitchState<EntityStateIdle>();
}

}  // namespace FA
