/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

//#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Id.h"
#include "MapData.h"
#include "PropertyData.h"
#include "SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityLifeQueue
{
public:
    struct CreatedItem
    {
        PropertyData propertyData_;
        Shared::MapData mapData_;
    };

public:
    void AddToCreationQueue(const PropertyData &data, const Shared::MapData &mapData);
    void AddToCreationQueue(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                            std::unordered_map<std::string, std::string> properties, const Shared::MapData &mapData);
    void AddToDeletionQueue(EntityId id);
    std::vector<CreatedItem> &&MoveCreationQueue();
    std::unordered_set<EntityId> &&MoveDeletionQueue();

private:
    std::vector<CreatedItem> creationQueue_;
    std::unordered_set<EntityId> deletionQueue_;
};

}  // namespace Entity

}  // namespace FA
