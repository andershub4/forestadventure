/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityLifeHandler.h"

namespace FA {

namespace Entity {

EntityLifeHandler::~EntityLifeHandler() = default;

void EntityLifeHandler::AddToCreationPool(const Shared::EntityData &data)
{
    creationPool_.push_back(data);
}

void EntityLifeHandler::AddToDeletionPool(EntityId id)
{
    deletionPool_.insert(id);
}

std::vector<Shared::EntityData> &&EntityLifeHandler::MoveCreationPool()
{
    return std::move(creationPool_);
}

std::unordered_set<EntityId> &&EntityLifeHandler::MoveDeletionPool()
{
    return std::move(deletionPool_);
}

}  // namespace Entity

}  // namespace FA
