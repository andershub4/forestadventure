/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityLifePool.h"

namespace FA {

namespace Entity {

void EntityLifePool::AddToCreationPool(const PropertyData &data)
{
    creationPool_.push_back(data);
}

void EntityLifePool::AddToCreationPool(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                                       std::unordered_map<std::string, std::string> properties)
{
    PropertyData data;
    data.typeStr_ = typeStr;
    data.position_ = pos;
    data.size_ = size;
    data.properties_ = properties;
    AddToCreationPool(data);
}

void EntityLifePool::AddToDeletionPool(EntityId id)
{
    deletionPool_.insert(id);
}

std::vector<PropertyData> &&EntityLifePool::MoveCreationPool()
{
    return std::move(creationPool_);
}

std::unordered_set<EntityId> &&EntityLifePool::MoveDeletionPool()
{
    return std::move(deletionPool_);
}

}  // namespace Entity

}  // namespace FA
