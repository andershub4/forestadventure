/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicMode.h"

#include "Entity/EntityService.h"
#include "Entity/Events/AttackEvent.h"
#include "Entity/Events/AttackWeapon.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Events/StopMoveEvent.h"
#include "Entity/Shapes/Shape.h"
#include "Enum/KeyboardKey.h"

namespace FA {

namespace Entity {

BasicMode::BasicMode(EntityService* owner)
    : owner_(owner)
{}

BasicMode::~BasicMode() = default;

void BasicMode::DrawTo(sf::RenderTarget& renderTarget)
{
    owner_->GetShape()->DrawTo(renderTarget);
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
    std::shared_ptr<BasicEvent> event = nullptr;

    if (key == Keyboard::Key::Right) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Right, FaceDirection::Right);
    }
    else if (key == Keyboard::Key::Left) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Left, FaceDirection::Left);
    }
    else if (key == Keyboard::Key::Up) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Up, FaceDirection::Up);
    }
    else if (key == Keyboard::Key::Down) {
        event = std::make_shared<StartMoveEvent>(MoveDirection::Down, FaceDirection::Down);
    }

    return event;
}

std::shared_ptr<BasicEvent> BasicMode::HandleIsKeyReleased(Keyboard::Key key)
{
    return std::make_shared<StopMoveEvent>();
}

std::shared_ptr<BasicEvent> BasicMode::HandleKeyPressed(Keyboard::Key key)
{
    std::shared_ptr<BasicEvent> event = nullptr;

    if (key == Keyboard::Key::RControl) {
        event = std::make_shared<AttackEvent>();
    }
    else if (key == Keyboard::Key::Space) {
        event = std::make_shared<AttackWeaponEvent>();
    }

    return event;
}

ModeType BasicMode::PollUpdate() const
{
    if (updateInfo_.cb_ != nullptr && updateInfo_.cb_(Owner()->GetShape())) {
        return updateInfo_.modeType_;
    }

    return ModeType::None;
}

}  // namespace Entity

}  // namespace FA
