/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityLifePool.h"

namespace FA {

namespace Entity {

void EntityLifePool::AddToCreationPool(const Shared::EntityData &data)
{
    creationPool_.push_back(data);
}

void EntityLifePool::AddToDeletionPool(EntityId id)
{
    deletionPool_.insert(id);
}

std::vector<Shared::EntityData> &&EntityLifePool::MoveCreationPool()
{
    return std::move(creationPool_);
}

std::unordered_set<EntityId> &&EntityLifePool::MoveDeletionPool()
{
    return std::move(deletionPool_);
}

}  // namespace Entity

}  // namespace FA
