/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityLifeQueue.h"

namespace FA {

namespace Entity {

void EntityLifeQueue::AddToCreationQueue(const PropertyData &data, const Shared::MapData &mapData)
{
    creationQueue_.push_back({data, mapData});
}

void EntityLifeQueue::AddToCreationQueue(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                                         std::unordered_map<std::string, std::string> properties,
                                         const Shared::MapData &mapData)
{
    PropertyData data;
    data.typeStr_ = typeStr;
    data.position_ = pos;
    data.size_ = size;
    data.properties_ = properties;
    AddToCreationQueue(data, mapData);
}

void EntityLifeQueue::AddToDeletionQueue(EntityId id)
{
    deletionQueue_.insert(id);
}

std::vector<EntityLifeQueue::CreatedItem> &&EntityLifeQueue::MoveCreationQueue()
{
    return std::move(creationQueue_);
}

std::unordered_set<EntityId> &&EntityLifeQueue::MoveDeletionQueue()
{
    return std::move(deletionQueue_);
}

}  // namespace Entity

}  // namespace FA
