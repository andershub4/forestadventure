/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "State.h"

#include "Abilities/AbilityIf.h"
#include "Body.h"
#include "Events/BasicEvent.h"
#include "Logging.h"

namespace FA {

namespace Entity {

State::State(StateType stateType, Body &body)
    : stateType_(stateType)
    , shape_(body)
    , enterCB_([]() {})
    , exitCB_([]() {})
{}

State::~State() = default;

void State::Enter(std::shared_ptr<BasicEvent> event)
{
    enterCB_();
    for (auto a : abilities_) {
        a->Enter(event);
    }
    shape_.Enter();
}

void State::Exit()
{
    exitCB_();
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

void State::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    if (!ignoreAllEvents_ || (notIgnorableEventTypes_.find(event->GetEventType()) != notIgnorableEventTypes_.end())) {
        auto eventType = event->GetEventType();
        if (eventCBs_.find(eventType) != eventCBs_.end()) {
            auto handler = eventCBs_.at(eventType);
            handler(event);
        }
        else {
            LOG_WARN("%s has no handler for %s", DUMP(stateType_), DUMP(eventType));
        }
    }
}

void State::RegisterEnterCB(std::function<void()> enterCB)
{
    enterCB_ = enterCB;
}

void State::RegisterExitCB(std::function<void()> exitCB)
{
    exitCB_ = exitCB;
}

void State::RegisterAbility(std::shared_ptr<AbilityIf> ability)
{
    abilities_.emplace_back(ability);
}

void State::RegisterMainSprite(std::shared_ptr<Graphic::SpriteIf> sprite)
{
    shape_.RegisterMainSprite(sprite);
}

void State::RegisterMainCollider(std::shared_ptr<Graphic::RectangleShapeIf> rect)
{
    shape_.RegisterMainCollider(rect);
}

void State::RegisterMainShapePart(std::shared_ptr<AnimationPartIf> part, std::shared_ptr<Graphic::SpriteIf> sprite)
{
    shape_.RegisterMainShapePart(part, sprite);
}

void State::RegisterMainColliderPart(std::shared_ptr<AnimationPartIf> part,
                                     std::shared_ptr<Graphic::RectangleShapeIf> rect)
{
    shape_.RegisterMainColliderPart(part, rect);
}

void State::RegisterShapePart(std::shared_ptr<AnimationPartIf> part)
{
    shape_.RegisterShapePart(part);
}

void State::RegisterColliderPart(std::shared_ptr<AnimationPartIf> part)
{
    shape_.RegisterColliderPart(part);
}

void State::RegisterEventCB(EventType eventType, std::function<void(std::shared_ptr<BasicEvent>)> event)
{
    if (eventCBs_.find(eventType) == eventCBs_.end()) {
        eventCBs_[eventType] = event;
    }
    else {
        LOG_ERROR("%s already exist", DUMP(eventType));
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

Shape State::GetShape() const
{
    return shape_;
}

}  // namespace Entity

}  // namespace FA
