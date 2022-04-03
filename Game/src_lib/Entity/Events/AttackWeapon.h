/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>

#include <SFML/System/Vector2.hpp>

#include "BasicEvent.h"

#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

struct AttackWeaponEvent : public BasicEvent
{
    AttackWeaponEvent(EntityType entityType, const std::unordered_map<FaceDirection, sf::Vector2f> &offset,
                      const std::unordered_map<FaceDirection, float> &rotation)
        : entityType_(entityType)
        , offset_(offset)
        , rotation_(rotation)
    {}

    virtual EventType GetEventType() const { return EventType::AttackWeapon; }

    EntityType entityType_ = EntityType::Unknown;
    std::unordered_map<FaceDirection, sf::Vector2f> offset_;
    std::unordered_map<FaceDirection, float> rotation_;
};

}  // namespace Entity

}  // namespace FA
