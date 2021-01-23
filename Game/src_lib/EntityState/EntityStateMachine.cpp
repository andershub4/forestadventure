/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityStateMachine.h"

#include "EntityState/State/EntityStateIdle.h"
#include "Utils/Logger.h"

namespace FA {

EntityStateMachine::EntityStateMachine(Entity& entity, FaceDirection faceDir, MoveDirection moveDir)
{
    stateData_.faceDir_ = faceDir;
    stateData_.moveDir_ = moveDir;
    currentState_ = std::make_unique<EntityStateIdle>(*this, entity, stateData_);
    // LOG_INFO("Enter ", currentState_->Name());
    currentState_->Enter();
}

EntityStateMachine::~EntityStateMachine()
{
    // LOG_INFO("Exit ", currentState_->Name());
    currentState_->Exit();
}

void EntityStateMachine::SetState(std::unique_ptr<EntityState> newState)
{
    // LOG_INFO("Exit ", currentState_->Name());
    currentState_->Exit();
    currentState_ = std::move(newState);
    // LOG_INFO("Enter ", currentState_->Name());
    currentState_->Enter();
}

void EntityStateMachine::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    currentState_->OnStartMove(moveDir, faceDir);
}

void EntityStateMachine::OnStopMove()
{
    currentState_->OnStopMove();
}

}  // namespace FA
