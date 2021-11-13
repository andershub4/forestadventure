/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateMachine.h"

#include "Logging.h"

namespace FA {

namespace Entity {

StateMachine::StateMachine(EntityService& entityService)
{}

StateMachine::~StateMachine()
{
    // LOG_INFO("Exit ", currentState_->Name());
    currentState_->Exit();
}

void StateMachine::Init(std::unique_ptr<BasicState> state)
{
    // LOG_INFO("Enter ", currentState_->Name());
    currentState_ = std::move(state);
    currentState_->Enter();
}

void StateMachine::HandleIsKeyPressed(Keyboard::Key key)
{
    currentState_->HandleIsKeyPressed(key);
}

void StateMachine::HandleKeyPressed(Keyboard::Key key)
{
    currentState_->HandleKeyPressed(key);
}

void StateMachine::HandleIsKeyReleased(Keyboard::Key key)
{
    currentState_->HandleIsKeyReleased(key);
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

}  // namespace Entity

}  // namespace FA
