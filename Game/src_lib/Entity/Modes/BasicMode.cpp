/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicMode.h"

#include "Entity/EntityService.h"
#include "Entity/Shapes/Shape.h"
#include "Enum/KeyboardKey.h"

namespace FA {

namespace Entity {

BasicMode::BasicMode(EntityService* entityService)
    : entityService_(entityService)
{}

BasicMode::~BasicMode() = default;

void BasicMode::DrawTo(sf::RenderTarget& renderTarget)
{
    entityService_->GetShape()->DrawTo(renderTarget);
}

void BasicMode::AddEvent(EventType eventType, ModeType modeType,
                         std::function<void(std::shared_ptr<BasicEvent> event)> cb)
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

std::shared_ptr<BasicEvent> BasicMode::HandleIsKeyPressed(Keyboard::Key key)
{
    return entityService_->HandleIsKeyPressed(key);
}

std::shared_ptr<BasicEvent> BasicMode::HandleIsKeyReleased(Keyboard::Key key)
{
    return entityService_->HandleIsKeyReleased(key);
}

std::shared_ptr<BasicEvent> BasicMode::HandleKeyPressed(Keyboard::Key key)
{
    return entityService_->HandleKeyPressed(key);
}

ModeType BasicMode::PollUpdate() const
{
    if (updateInfo_.cb_ != nullptr && updateInfo_.cb_(entityService_->GetShape())) {
        return updateInfo_.modeType_;
    }

    return ModeType::None;
}

}  // namespace Entity

}  // namespace FA
