/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityStateIdle.h"

#include "Entity/Entity.h"
#include "EntityStateMove.h"

namespace FA {

EntityStateIdle::EntityStateIdle(EntityStateMachine& stateMachine, Entity& entity, StateData& stateData)
    : EntityState(stateMachine, entity, stateData)
{}

EntityStateIdle::~EntityStateIdle() = default;

void EntityStateIdle::Enter()
{
    entity_.StartIdle(stateData_.moveDir_, stateData_.faceDir_, FrameType::Idle);
}

void EntityStateIdle::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateData_.moveDir_ = moveDir;
    stateData_.faceDir_ = faceDir;
    SwitchState<EntityStateMove>();
}

}  // namespace FA
