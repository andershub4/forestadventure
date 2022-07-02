/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEvent.h"

namespace FA {

namespace Entity {

struct DeadEvent : public BasicEvent
{
    virtual EventType GetEventType() const { return EventType::Dead; }
};

}  // namespace Entity

}  // namespace FA
