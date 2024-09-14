/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEvent.h"

namespace FA {

namespace Entity {

struct StaticCollisionEvent : public BasicEvent
{
    virtual EventType GetEventType() const { return EventType::StaticCollision; }
};

}  // namespace Entity

}  // namespace FA
