/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicMode.h"

#include "Entity/EntityService.h"
#include "Entity/Shapes/Shape.h"
#include "Logging.h"

namespace FA {

namespace Entity {

BasicMode::BasicMode(EntityService& entityService)
    : entityService_(entityService)
{}

BasicMode::~BasicMode() = default;

void BasicMode::DrawTo(sf::RenderTarget& renderTarget)
{
    entityService_.GetShape()->DrawTo(renderTarget);
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

}  // namespace Entity

}  // namespace FA
