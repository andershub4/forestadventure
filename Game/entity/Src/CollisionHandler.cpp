/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CollisionHandler.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "EntityDb.h"
#include "EntityIf.h"

namespace FA {

namespace Entity {

CollisionHandler::CollisionHandler(const EntityDb &entityDb)
    : entityDb_(entityDb)
{}

CollisionHandler::~CollisionHandler() = default;

void CollisionHandler::AddCollider(EntityId id)
{
    const auto &entity = entityDb_.GetEntity(id);
    bool isStatic = entity.IsStatic();

    if (isStatic) {
        staticEntities_.insert(id);
    }
    else {
        entities_.insert(id);
    }
}

void CollisionHandler::RemoveCollider(EntityId id)
{
    const auto &entity = entityDb_.GetEntity(id);
    bool isStatic = entity.IsStatic();

    if (isStatic) {
        staticEntities_.erase(id);
    }
    else {
        entities_.erase(id);
    }
}

void CollisionHandler::DetectCollisions()
{
    for (const auto id : entities_) {
        DetectEntityCollisions(id);
        DetectStaticCollisions(id);
    }
}

void CollisionHandler::DetectOutsideTileMap(const sf::Vector2u &mapSize)
{
    auto rect = sf::FloatRect({0.0f, 0.0f}, static_cast<sf::Vector2f>(mapSize));

    for (const auto id : entities_) {
        const auto &entity = entityDb_.GetEntity(id);
        bool isOutside = entity.IsOutsideTileMap(rect);
        if (isOutside) {
            entitiesOutsideTileMap_.insert(id);
        }
    }
}

void CollisionHandler::DetectEntityCollisions(EntityId id)
{
    for (const auto otherId : entities_) {
        if (id != otherId) {
            DetectCollision(id, otherId);
        }
    }
}

void CollisionHandler::DetectStaticCollisions(EntityId id)
{
    for (const auto otherId : staticEntities_) {
        DetectCollision(id, otherId);
    }
}

void CollisionHandler::DetectCollision(EntityId id, EntityId otherId)
{
    std::pair<EntityId, EntityId> pair{id, otherId};
    bool found = collisionPairs_.find(pair) != collisionPairs_.end();
    if (!found) {
        const auto &entity = entityDb_.GetEntity(id);
        const auto &otherEntity = entityDb_.GetEntity(otherId);
        bool intersect = entity.Intersect(otherEntity);
        if (intersect) {
            collisionPairs_.insert(pair);
        }
    }
}

void CollisionHandler::HandleCollisions()
{
    for (const auto &pair : collisionPairs_) {
        auto &first = entityDb_.GetEntity(pair.first);
        auto &second = entityDb_.GetEntity(pair.second);
        first.HandleCollision(pair.second);
        second.HandleCollision(pair.first);
    }
    collisionPairs_.clear();
}

void CollisionHandler::HandleOutsideTileMap()
{
    for (const auto id : entitiesOutsideTileMap_) {
        auto &entity = entityDb_.GetEntity(id);
        entity.HandleOutsideTileMap();
    }
    entitiesOutsideTileMap_.clear();
}

}  // namespace Entity

}  // namespace FA
