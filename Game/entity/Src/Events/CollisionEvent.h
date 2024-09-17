/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEvent.h"

#include "Id.h"

namespace FA {

namespace Entity {

struct CollisionEvent : public BasicEvent
{
    CollisionEvent(EntityId id, bool isSolid)
        : id_(id)
        , isSolid_(isSolid)
    {}

    virtual EventType GetEventType() const { return EventType::Collision; }

    EntityId id_ = InvalidEntityId;
    bool isSolid_{false};
};

}  // namespace Entity

}  // namespace FA
