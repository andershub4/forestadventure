/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_set>

#include "Id.h"
#include "SfmlFwd.h"

namespace FA {

namespace Entity {

class CollisionHandlerIf2
{
public:
    virtual ~CollisionHandlerIf2() = default;

    virtual void DetectCollisions(const std::unordered_set<EntityId> &entities,
                                  const std::unordered_set<EntityId> &staticEntities) = 0;
    virtual void DetectOutsideTileMap(const sf::Vector2u &mapSize, const std::unordered_set<EntityId> &entities) = 0;
    virtual void HandleCollisions() = 0;
    virtual void HandleOutsideTileMap() = 0;

protected:
    CollisionHandlerIf2() = default;
    CollisionHandlerIf2(const CollisionHandlerIf2 &) = default;
    CollisionHandlerIf2(CollisionHandlerIf2 &&) = default;
    CollisionHandlerIf2 &operator=(const CollisionHandlerIf2 &) = default;
    CollisionHandlerIf2 &operator=(CollisionHandlerIf2 &&) = default;
};

}  // namespace Entity

}  // namespace FA
