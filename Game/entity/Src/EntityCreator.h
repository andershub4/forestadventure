/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Id.h"
#include "MapData.h"
#include "PropertyData.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

struct TileGraphic;

}  // namespace Shared

namespace Entity {

class BasicEntity;
class Factory;
class EntityDb;
class EntityService;

class EntityCreator
{
public:
    EntityCreator(EntityDb &entityDb);

    void RegisterOnCreateFn(std::function<void(BasicEntity &)> fn);
    void RegisterOnDeleteFn(std::function<void(BasicEntity &)> fn);
    void CreateEntity(const PropertyData &data, const Shared::MapData &mapData);
    void CreateEntity(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                      std::unordered_map<std::string, std::string> properties, const Shared::MapData &mapData);
    void CreateTileEntity(const sf::Vector2f &pos, const Shared::TileGraphic &graphic, const Shared::MapData &mapData);
    void DeleteEntity(EntityId id);
    void HandleCreatedEntities(const Factory &factory, const EntityService &service);
    void HandleDeletedEntities();

private:
    EntityDb &entityDb_;

    struct CreatedItem
    {
        PropertyData propertyData_;
        Shared::MapData mapData_;
    };

    std::vector<CreatedItem> createdEntities_;
    std::unordered_set<EntityId> deletedEntities_;
    std::function<void(BasicEntity &)> onCreateFn_;
    std::function<void(BasicEntity &)> onDeleteFn_;
};

}  // namespace Entity

}  // namespace FA
