/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicMode.h"

#include "Entity/EntityService.h"
#include "Entity/Events/BasicEvent.h"
#include "Entity/ModeController.h"
#include "Entity/Shape.h"
#include "Logging.h"

namespace FA {

namespace Entity {

BasicMode::BasicMode(EntityService& entityService, ModeController& modeController)
    : entityService_(entityService)
    , modeController_(modeController)
{}

BasicMode::~BasicMode() = default;

void BasicMode::DrawTo(sf::RenderTarget& renderTarget)
{
    entityService_.GetShape()->DrawTo(renderTarget);
}

void BasicMode::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    auto action = GetAction(event->GetEventType());
    DoAction(action, event);
}

void BasicMode::BindAction(const Action& action, EventType eventType)
{
    eventMap_[eventType] = action;
}

void BasicMode::BindActionDuringUpdate(const Action& action, std::function<bool(std::shared_ptr<Shape>)> condition)
{
    actionCondition_ = condition;
    nextAction_ = action;
}

Action BasicMode::GetAction(EventType eventType) const
{
    auto it = eventMap_.find(eventType);
    if (it != eventMap_.end()) {
        return eventMap_.at(eventType);
    }
    else {
        LOG_ERROR("ModeType ", GetModeType(), " can't handle ", eventType);
        return {};
    }
}

Action BasicMode::PollAction() const
{
    if (actionCondition_(entityService_.GetShape())) {
        return nextAction_;
    }

    return {};
}

BasicMode::Direction& BasicMode::AddDirection(FaceDirection faceDirection)
{
    auto it = directions_.find(faceDirection);

    if (it == directions_.end()) {
        directions_[faceDirection] = BasicMode::Direction();
    }
    else {
        LOG_ERROR("faceDirection: ", faceDirection, " already exist");
    }

    return directions_.at(faceDirection);
}

Animation BasicMode::GetAnimation(FaceDirection faceDirection) const
{
    auto it = directions_.find(faceDirection);

    if (it != directions_.end()) {
        return directions_.at(faceDirection).animation_;
    }
    else {
        return Animation();
    }
}

Image BasicMode::GetImage(FaceDirection faceDirection) const
{
    auto it = directions_.find(faceDirection);

    if (it != directions_.end()) {
        return directions_.at(faceDirection).image_;
    }
    else {
        return Image();
    }
}

void BasicMode::DoAction(const Action& action, std::shared_ptr<BasicEvent> event)
{
    if (action.cb_) action.cb_(event);

    auto nextModeType = action.modeType_;
    if (nextModeType != ModeType::None) {
        modeController_.ChangeModeTo(nextModeType, event);
    }
}

void BasicMode::BasicUpdate()
{
    auto action = PollAction();
    DoAction(action);
}

}  // namespace Entity

}  // namespace FA
