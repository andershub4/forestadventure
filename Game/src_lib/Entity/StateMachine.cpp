/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateMachine.h"

#include "Events/BasicEvent.h"
#include "States/State.h"

namespace FA {

namespace Entity {

StateMachine::StateMachine()
{
    currentState_ = RegisterState(StateType::Uninitialized);
    currentState_->Enter(nullptr);
}

StateMachine::~StateMachine()
{
    currentState_->Exit();
}

void StateMachine::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    currentState_->HandleEvent(event);
}

void StateMachine::QueueInitEvents(std::shared_ptr<BasicEvent> event)
{
    queuedInitEvents_.push_back(event);
}

void StateMachine::HandleQueuedInitEvents()
{
    for (auto event : queuedInitEvents_) {
        HandleEvent(event);
    }
    queuedInitEvents_.clear();
}

void StateMachine::Update(float deltaTime)
{
    currentState_->Update(deltaTime);
}

std::shared_ptr<State> StateMachine::RegisterState(StateType stateType, bool startState)
{
    auto state = std::make_shared<State>(stateType, *this);
    InitState(state, startState);
    return state;
}

void StateMachine::InitState(std::shared_ptr<State> state, bool startState)
{
    state->BindAction(Action::Call(onDestroy_), EventType::Destroy);

    auto stateType = state->GetStateType();
    states_[stateType] = state;

    if (startState) {
        auto u = states_.at(StateType::Uninitialized);
        u->BindAction(Action::ChangeTo(stateType), EventType::Init);
    }
}

void StateMachine::RegisterCreateCB(std::function<void(std::shared_ptr<BasicEvent>)> onCreate)
{
    auto u = states_.at(StateType::Uninitialized);
    u->BindAction(Action::Call(onCreate), EventType::Create);
}

void StateMachine::RegisterDestroyCB(std::function<void(std::shared_ptr<BasicEvent>)> onDestroy)
{
    onDestroy_ = onDestroy;
}

void StateMachine::ChangeStateTo(StateType nextStateType, std::shared_ptr<BasicEvent> event)
{
    currentState_->Exit();
    currentState_ = states_.at(nextStateType);
    currentState_->Enter(event);
}

}  // namespace Entity

}  // namespace FA
