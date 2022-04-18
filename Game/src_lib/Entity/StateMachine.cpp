/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StateMachine.h"

#include "EntityService.h"
#include "Events/BasicEvent.h"
#include "States/UninitializedState.h"

namespace FA {

namespace Entity {

StateMachine::StateMachine(EntityService& entityService)
    : entityService_(entityService)
{
    currentState_ = RegisterState<UninitializedState>();
    currentState_->Enter(nullptr);
}

StateMachine::~StateMachine()
{
    currentState_->Exit();
}

std::shared_ptr<BasicState> StateMachine::GetState(StateType stateType) const
{
    return states_.at(stateType);
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

void StateMachine::DrawTo(sf::RenderTarget& renderTarget)
{
    currentState_->DrawTo(renderTarget);
}

void StateMachine::RegisterState(std::shared_ptr<BasicState> state, bool startState)
{
    state->BindAction(Action::Call(onDestroy_), EventType::Destroy);

    auto stateType = state->GetStateType();
    states_[stateType] = state;
    state->Register();

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
