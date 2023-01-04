/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Entity/EventType.h"

namespace FA {

namespace Entity {

struct BasicEvent
{
    virtual EventType GetEventType() const = 0;
};

}  // namespace Entity

}  // namespace FA
