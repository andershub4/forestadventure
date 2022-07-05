/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateMachine.h"

#include "Events/BasicEvent.h"
#include "State.h"

namespace FA {

namespace Entity {

StateMachine::StateMachine() = default;

StateMachine::~StateMachine()
{
    currentState_->Exit();
}

void StateMachine::SetStartState(std::shared_ptr<State> state)
{
    currentState_ = state;
    currentState_->Enter(nullptr);
}

void StateMachine::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    currentState_->HandleEvent(event);
}

void StateMachine::Update(float deltaTime)
{
    currentState_->Update(deltaTime);
}

std::shared_ptr<State> StateMachine::RegisterState(StateType stateType /*, bool startState*/)
{
    auto state = std::make_shared<State>(stateType);
    states_[stateType] = state;
    return state;
}

void StateMachine::ChangeStateTo(StateType nextStateType, std::shared_ptr<BasicEvent> event)
{
    currentState_->Exit();
    currentState_ = states_.at(nextStateType);
    currentState_->Enter(event);
}

}  // namespace Entity

}  // namespace FA
