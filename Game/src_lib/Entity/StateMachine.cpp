/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateMachine.h"

#include "Logging.h"
#include "States/UninitializedState.h"

namespace FA {

namespace Entity {

StateMachine::StateMachine(EntityService& entityService)
{
    currentState_ = std::make_unique<UninitializedState>(*this, stateData_, entityService);
    // LOG_INFO("Enter ", currentState_->Name());
    currentState_->Enter();
}

StateMachine::~StateMachine()
{
    // LOG_INFO("Exit ", currentState_->Name());
    currentState_->Exit();
}

void StateMachine::Create(const PropertyData& data)
{
    currentState_->Create(data);
}

void StateMachine::Update(float deltaTime)
{
    currentState_->Update(deltaTime);
}

void StateMachine::LateUpdate()
{
    currentState_->LateUpdate();
}

void StateMachine::DrawTo(sf::RenderTarget& renderTarget)
{
    currentState_->DrawTo(renderTarget);
}

void StateMachine::SetState(std::unique_ptr<BasicState> newState)
{
    // LOG_INFO("Exit ", currentState_->Name());
    currentState_->Exit();
    currentState_ = std::move(newState);
    // LOG_INFO("Enter ", currentState_->Name());
    currentState_->Enter();
}

void StateMachine::OnInitStateData()
{
    currentState_->OnInitStateData();
}

void StateMachine::OnStartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    currentState_->OnStartMove(moveDir, faceDir);
}

void StateMachine::OnStopMove()
{
    currentState_->OnStopMove();
}

void StateMachine::OnAttack()
{
    currentState_->OnAttack();
}

void StateMachine::OnAttackWeapon()
{
    currentState_->OnAttackWeapon();
}

}  // namespace Entity

}  // namespace FA
