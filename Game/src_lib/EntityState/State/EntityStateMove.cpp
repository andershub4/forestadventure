/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityStateMove.h"

#include "Entity/Entity.h"
#include "EntityStateIdle.h"

namespace FA {

EntityStateMove::EntityStateMove(EntityStateMachine& stateMachine, Entity& entity, StateData& stateData)
    : EntityState(stateMachine, entity, stateData)
{}

EntityStateMove::~EntityStateMove() = default;

void EntityStateMove::Enter()
{
    entity_.StartMove(stateData_.moveDir_, stateData_.faceDir_, FrameType::Move);
}

void EntityStateMove::Exit()
{
    entity_.StopMove(stateData_.moveDir_, stateData_.faceDir_);
}

void EntityStateMove::OnStopMove()
{
    SwitchState<EntityStateIdle>();
}

}  // namespace FA
