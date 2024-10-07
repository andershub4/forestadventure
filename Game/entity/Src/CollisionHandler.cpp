/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CollisionHandler.h"

#include "Entities/BasicEntity.h"
#include "EntityDb.h"

namespace FA {

namespace Entity {

CollisionHandler::CollisionHandler(const EntityDb &entityDb)
    : entityDb_(entityDb)
{}

void CollisionHandler::AddCollider(EntityId id, bool isStatic)
{
    if (isStatic) {
        staticEntities_.insert(id);
    }
    else {
        entities_.insert(id);
    }
}

void CollisionHandler::RemoveCollider(EntityId id, bool isStatic)
{
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
        first.HandleCollision(pair.second, entityDb_.GetEntity(pair.second).IsSolid());
        second.HandleCollision(pair.first, entityDb_.GetEntity(pair.first).IsSolid());
    }
    collisionPairs_.clear();
}

}  // namespace Entity

}  // namespace FA
