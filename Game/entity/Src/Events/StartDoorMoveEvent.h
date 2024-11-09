/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEvent.h"

#include <SFML/System/Vector2.hpp>

namespace FA {

namespace Entity {

struct StartDoorMoveEvent : public BasicEvent
{
    StartDoorMoveEvent(const sf::Vector2f &exitPosition)
        : exitPosition_(exitPosition)
    {}

    virtual EventType GetEventType() const { return EventType::StartDoorMove; }

    sf::Vector2f exitPosition_;
};

}  // namespace Entity

}  // namespace FA
