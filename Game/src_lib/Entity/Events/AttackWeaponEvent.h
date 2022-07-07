/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEvent.h"

#include "Enum/EntityType.h"

namespace FA {

namespace Entity {

struct AttackWeaponEvent : public BasicEvent
{
    AttackWeaponEvent(EntityType entityType)
        : entityType_(entityType)
    {}

    virtual EventType GetEventType() const { return EventType::AttackWeapon; }

    EntityType entityType_ = EntityType::Unknown;
};

}  // namespace Entity

}  // namespace FA
