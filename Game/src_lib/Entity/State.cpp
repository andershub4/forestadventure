/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "State.h"

#include "Entity/Abilities/BasicAbility.h"
#include "Entity/Events/BasicEvent.h"
#include "Logging.h"

namespace FA {

namespace Entity {

State::State(StateType stateType)
    : stateType_(stateType)
{}

State::~State() = default;

void State::Enter(std::shared_ptr<BasicEvent> event)
{
    for (auto a : abilities_) {
        a->Enter(event);
    }
}

void State::Exit()
{
    for (auto a : abilities_) {
        a->Exit();
    }
}

void State::Update(float deltaTime)
{
    for (auto a : abilities_) {
        a->Update(deltaTime);
    }
}

void State::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    if (!ignoreAllEvents_) {
        auto t = event->GetEventType();
        auto handler = eventCBs_.at(t);
        handler(event);
    }
}

void State::RegisterAbility(std::shared_ptr<BasicAbility> ability)
{
    abilities_.emplace_back(ability);
}

void State::RegisterEventCB(EventType eventType, std::function<void(std::shared_ptr<BasicEvent>)> event)
{
    if (eventCBs_.find(eventType) == eventCBs_.end()) {
        eventCBs_[eventType] = event;
    }
    else {
        LOG_ERROR("eventType: ", eventType, " already exist");
    }
}

void State::RegisterIgnoreEvents(const std::vector<EventType> &eventTypes)
{
    for (const auto &e : eventTypes) {
        RegisterEventCB(e, [](std::shared_ptr<BasicEvent>) {});
    }
}

void State::IgnoreAllEvents()
{
    ignoreAllEvents_ = true;
}

}  // namespace Entity

}  // namespace FA
