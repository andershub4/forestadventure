/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicState.h"

#include "Entity/Abilities/BasicAbility.h"
#include "Entity/Events/BasicEvent.h"
#include "Entity/StateMachine.h"
#include "Logging.h"

namespace FA {

namespace Entity {

BasicState::BasicState(StateType stateType, StateMachine& stateMachine)
    : stateMachine_(stateMachine)
    , stateType_(stateType)
{}

BasicState::~BasicState() = default;

void BasicState::Enter(std::shared_ptr<BasicEvent> event)
{
    for (auto a : abilities_) {
        a->Enter(event);
    }
}

void BasicState::Exit()
{
    for (auto a : abilities_) {
        a->Exit();
    }
}

void BasicState::Update(float deltaTime)
{
    for (auto a : abilities_) {
        a->Update(deltaTime);
    }
}

void BasicState::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    auto action = GetAction(event->GetEventType());
    DoAction(action, event);
}

void BasicState::BindAction(const Action& action, EventType eventType)
{
    eventMap_[eventType] = action;
}

void BasicState::RegisterAbility(std::shared_ptr<BasicAbility> ability)
{
    abilities_.emplace_back(ability);
}

Action BasicState::GetAction(EventType eventType) const
{
    auto it = eventMap_.find(eventType);
    if (it != eventMap_.end()) {
        return eventMap_.at(eventType);
    }
    else {
        LOG_ERROR("stateType ", GetStateType(), " can't handle ", eventType);
        return {};
    }
}

void BasicState::DoAction(const Action& action, std::shared_ptr<BasicEvent> event)
{
    if (action.cb_) action.cb_(event);

    auto nextStateType = action.stateType_;
    if (nextStateType != StateType::None) {
        stateMachine_.ChangeStateTo(nextStateType, event);
    }
}

}  // namespace Entity

}  // namespace FA
