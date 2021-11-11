/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicMode.h"

#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

BasicMode::BasicMode(EntityService *owner)
    : owner_(owner)
{}

BasicMode::~BasicMode() = default;

void BasicMode::AddEvent(EventType eventType, ModeType modeType, std::function<void(std::shared_ptr<BasicEvent> event)> cb)
{
    eventMap_[eventType] = {modeType, cb};
}

void BasicMode::AddUpdateFn(std::function<bool(std::shared_ptr<Shape>)> updateFn, ModeType modeType)
{
    updateInfo_ = {modeType, updateFn};
}

Action BasicMode::GetAction(EventType eventType) const
{
    auto it = eventMap_.find(eventType);
    if (it == eventMap_.end()) {
        return {};
    }
    else {
        return eventMap_.at(eventType);
    }
}

UpdateInfo BasicMode::GetUpdateInfo() const
{
    return updateInfo_;
}

}  // namespace Entity

}  // namespace FA
