/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "CollisionHandlerIf.h"

namespace FA {

namespace Entity {

class CollisionHandlerMock : public CollisionHandlerIf2
{
public:
    MOCK_METHOD((void), DetectCollisions, (const std::unordered_set<EntityId> &, const std::unordered_set<EntityId> &),
                (override));
    MOCK_METHOD((void), DetectOutsideTileMap, (const sf::Vector2u &, const std::unordered_set<EntityId> &), (override));
    MOCK_METHOD((void), HandleCollisions, (), (override));
    MOCK_METHOD((void), HandleOutsideTileMap, (), (override));
};

}  // namespace Entity

}  // namespace FA
