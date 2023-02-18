/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "State.h"

#include "Abilities/BasicAbility.h"
#include "Body.h"
#include "Events/BasicEvent.h"
#include "Logging.h"

namespace FA {

namespace Entity {

State::State(StateType stateType, Body &body)
    : stateType_(stateType)
    , shape_(body)
    , beginCB_([]() {})
{}

State::~State() = default;

void State::Enter(std::shared_ptr<BasicEvent> event)
{
    beginCB_();
    for (auto a : abilities_) {
        a->Enter(event);
    }
    shape_.Enter();
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
    shape_.Update(deltaTime);
}

void State::DrawTo(sf::RenderTarget &renderTarget)
{
    shape_.DrawTo(renderTarget);
}

void State::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    if (!ignoreAllEvents_ || (notIgnorableEventTypes_.find(event->GetEventType()) != notIgnorableEventTypes_.end())) {
        auto t = event->GetEventType();
        auto handler = eventCBs_.at(t);
        handler(event);
    }
}

void State::RegisterBeginCB(std::function<void()> beginCB)
{
    beginCB_ = beginCB;
}

void State::RegisterAbility(std::shared_ptr<BasicAbility> ability)
{
    abilities_.emplace_back(ability);
}

void State::RegisterSprite(std::shared_ptr<BasicSprite> sprite)
{
    shape_.RegisterSprite(sprite);
}

void State::RegisterEventCB(EventType eventType, std::function<void(std::shared_ptr<BasicEvent>)> event)
{
    if (eventCBs_.find(eventType) == eventCBs_.end()) {
        eventCBs_[eventType] = event;
    }
    else {
        LOG_ERROR("eventType: %u already exist", eventType);
    }
}

void State::RegisterIgnoreEvents(const std::vector<EventType> &eventTypes)
{
    for (const auto &e : eventTypes) {
        RegisterEventCB(e, [](std::shared_ptr<BasicEvent>) {});
    }
}

void State::IgnoreAllEventsExcept(const std::unordered_set<EventType> &notIgnorableEventTypes)
{
    notIgnorableEventTypes_ = notIgnorableEventTypes;
    ignoreAllEvents_ = true;
}

}  // namespace Entity

}  // namespace FA
