/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateMachine.h"

#include "States/IdleState.h"
#include "Utils/Logger.h"

namespace FA {

namespace Entity {

StateMachine::StateMachine(sf::RectangleShape* rectShape, FaceDirection faceDir, MoveDirection moveDir,
                           const AnimationFactory& animationFactory, float velocity)
{
    stateData_.faceDir_ = faceDir;
    stateData_.moveDir_ = moveDir;
    stateData_.velocity_ = velocity;
    stateData_.rectShape_ = rectShape;
    currentState_ = std::make_unique<IdleState>(*this, animationFactory, stateData_);
    // LOG_INFO("Enter ", currentState_->Name());
    currentState_->Enter();
}

StateMachine::~StateMachine()
{
    // LOG_INFO("Exit ", currentState_->Name());
    currentState_->Exit();
}

void StateMachine::Update(float deltaTime)
{
    currentState_->Update(deltaTime);
}

void StateMachine::SetState(std::unique_ptr<BasicState> newState)
{
    // LOG_INFO("Exit ", currentState_->Name());
    currentState_->Exit();
    currentState_ = std::move(newState);
    // LOG_INFO("Enter ", currentState_->Name());
    currentState_->Enter();
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
