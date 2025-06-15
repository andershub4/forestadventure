/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <set>
#include <unordered_set>

#include "CollisionHandlerIf.h"

#include "Id.h"
#include "SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityDb;

class CollisionHandler
{
public:
    CollisionHandler(const EntityDb &entityDb);
    ~CollisionHandler();

    void AddCollider(EntityId id);
    void RemoveCollider(EntityId id);
    void DetectCollisions();
    void DetectOutsideTileMap(const sf::Vector2u &mapSize);
    void HandleCollisions();
    void HandleOutsideTileMap();

private:
    template <typename T>
    struct customPairLess
    {
        bool operator()(const std::pair<T, T> &lhs, const std::pair<T, T> &rhs) const
        {
            const auto lhs_order = lhs.first < lhs.second ? lhs : std::tie(lhs.second, lhs.first);
            const auto rhs_order = rhs.first < rhs.second ? rhs : std::tie(rhs.second, rhs.first);

            return lhs_order < rhs_order;
        }
    };

    const EntityDb &entityDb_;

    std::unordered_set<EntityId> entities_;
    std::unordered_set<EntityId> staticEntities_;
    std::unordered_set<EntityId> entitiesOutsideTileMap_;
    std::set<std::pair<EntityId, EntityId>, customPairLess<EntityId>> collisionPairs_;

private:
    void DetectEntityCollisions(EntityId id);
    void DetectStaticCollisions(EntityId id);
    void DetectCollision(EntityId id, EntityId otherId);
};

class CollisionHandler2 : public CollisionHandlerIf2
{
public:
    CollisionHandler2(const EntityDb &entityDb);
    ~CollisionHandler2();

    virtual void DetectCollisions(const std::unordered_set<EntityId> &entities,
                                  const std::unordered_set<EntityId> &staticEntities) override;
    virtual void DetectOutsideTileMap(const sf::Vector2u &mapSize,
                                      const std::unordered_set<EntityId> &entities) override;
    virtual void HandleCollisions() override;
    virtual void HandleOutsideTileMap() override;

private:
    template <typename T>
    struct customPairLess
    {
        bool operator()(const std::pair<T, T> &lhs, const std::pair<T, T> &rhs) const
        {
            const auto lhs_order = lhs.first < lhs.second ? lhs : std::tie(lhs.second, lhs.first);
            const auto rhs_order = rhs.first < rhs.second ? rhs : std::tie(rhs.second, rhs.first);

            return lhs_order < rhs_order;
        }
    };

    const EntityDb &entityDb_;

    std::unordered_set<EntityId> entitiesOutsideTileMap_;
    std::set<std::pair<EntityId, EntityId>, customPairLess<EntityId>> collisionPairs_;

private:
    void DetectEntityCollisions(EntityId id, const std::unordered_set<EntityId> &entities);
    void DetectStaticCollisions(EntityId id, const std::unordered_set<EntityId> &staticEntities);
    void DetectCollision(EntityId id, EntityId otherId);
};

}  // namespace Entity

}  // namespace FA
