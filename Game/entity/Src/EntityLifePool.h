/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Id.h"
#include "PropertyData.h"
#include "SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityLifePool
{
public:
    void AddToCreationPool(const PropertyData &data);
    void AddToCreationPool(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                           std::unordered_map<std::string, std::string> properties);
    void AddToDeletionPool(EntityId id);
    std::vector<PropertyData> &&MoveCreationPool();
    std::unordered_set<EntityId> &&MoveDeletionPool();

private:
    std::vector<PropertyData> creationPool_;
    std::unordered_set<EntityId> deletionPool_;
};

}  // namespace Entity

}  // namespace FA
