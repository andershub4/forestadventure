/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicState.h"

#include "Entity/EntityService.h"
#include "Entity/Events/BasicEvent.h"
#include "Entity/Shape.h"
#include "Entity/StateMachine.h"
#include "Logging.h"

namespace FA {

namespace Entity {

BasicState::BasicState(EntityService& entityService, StateMachine& stateMachine)
    : entityService_(entityService)
    , stateMachine_(stateMachine)
{}

BasicState::~BasicState() = default;

void BasicState::DrawTo(sf::RenderTarget& renderTarget)
{
    entityService_.GetShape()->DrawTo(renderTarget);
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

void BasicState::BindActionDuringUpdate(const Action& action, std::function<bool(std::shared_ptr<Shape>)> condition)
{
    actionCondition_ = condition;
    nextAction_ = action;
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

Action BasicState::PollAction() const
{
    if (actionCondition_(entityService_.GetShape())) {
        return nextAction_;
    }

    return {};
}

Animation BasicState::GetAnimation() const
{
    if (animationFn_)
        return animationFn_(entityService_);
    else {
        return Animation();
    }
}

Image BasicState::GetImage() const
{
    if (imageFn_) {
        return imageFn_(entityService_);
    }
    else {
        return Image();
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

void BasicState::BasicUpdate()
{
    auto action = PollAction();
    DoAction(action);
}

}  // namespace Entity

}  // namespace FA
