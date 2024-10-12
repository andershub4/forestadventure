/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityCreator.h"

#include <memory>

#include "Entities/BasicEntity.h"
#include "EntityDb.h"
#include "EntityService.h"
#include "Factory.h"

namespace FA {

namespace Entity {

EntityCreator::EntityCreator(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                             const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews,
                             const Factory &factory, EntityDb &entityDb)
    : messageBus_(messageBus)
    , textureManager_(textureManager)
    , sheetManager_(sheetManager)
    , cameraViews_(cameraViews)
    , factory_(factory)
    , entityDb_(entityDb)
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

void EntityCreator::DeleteEntity(EntityId id)
{
    deletedEntities_.insert(id);
}

void EntityCreator::HandleCreatedEntities()
{
    for (const auto data : createdEntities_) {
        auto service = std::make_unique<EntityService>(messageBus_, textureManager_, sheetManager_, cameraViews_,
                                                       entityDb_, *this);
        auto entity = factory_.Create(data.propertyData_, data.mapData_, std::move(service));
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
