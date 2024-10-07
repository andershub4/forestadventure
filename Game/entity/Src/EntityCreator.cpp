/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityCreator.h"

#include "Entities/BasicEntity.h"
#include "Entities/TileEntity.h"
#include "EntityDb.h"
#include "Factory.h"

namespace FA {

namespace Entity {

EntityCreator::EntityCreator(EntityDb &entityDb)
    : entityDb_(entityDb)
{}

void EntityCreator::RegisterOnCreateFn(std::function<void(BasicEntity &)> fn)
{
    onCreateFn_ = fn;
}

void EntityCreator::RegisterOnDeleteFn(std::function<void(BasicEntity &)> fn)
{
    onDeleteFn_ = fn;
}

void EntityCreator::CreateEntity(const PropertyData &data, const Shared::MapData &mapData)
{
    createdEntities_.push_back({data, mapData});
}

void EntityCreator::CreateEntity(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                                 std::unordered_map<std::string, std::string> properties,
                                 const Shared::MapData &mapData)
{
    PropertyData data;
    data.typeStr_ = typeStr;
    data.position_ = pos;
    data.size_ = size;
    data.properties_ = properties;
    CreateEntity(data, mapData);
}

void EntityCreator::CreateTileEntity(const sf::Vector2f &pos, const Shared::TileGraphic &graphic,
                                     const Shared::MapData &mapData)
{
    PropertyData data;
    data.typeStr_ = TileEntity::str;
    data.position_ = pos;
    data.graphic_ = graphic;
    CreateEntity(data, mapData);
}

void EntityCreator::DeleteEntity(EntityId id)
{
    deletedEntities_.insert(id);
}

void EntityCreator::HandleCreatedEntities(const Factory &factory, const EntityService &service)
{
    for (const auto data : createdEntities_) {
        auto entity = factory.Create(data.propertyData_, data.mapData_, service);
        entity->Init();
        onCreateFn_(*entity);
        entityDb_.AddEntity(std::move(entity));
    }
    createdEntities_.clear();
}

void EntityCreator::HandleDeletedEntities()
{
    for (const auto id : deletedEntities_) {
        auto &entity = entityDb_.GetEntity(id);
        entity.Destroy();
        onDeleteFn_(entity);
        entityDb_.DeleteEntity(id);
    }

    deletedEntities_.clear();
}
}  // namespace Entity

}  // namespace FA
