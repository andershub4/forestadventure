/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <sstream>

#include "EntityManager.h"

#include "Entity/Entities/BasicEntity.h"
#include "Entity/Entities/TileEntity.h"
#include "Entity/PropertyData.h"
#include "Logging.h"

namespace FA {

namespace Entity {

EntityManager::EntityManager(Shared::MessageBus& messageBus, const Shared::SheetManager& sheetManager,
                             const Shared::CameraManager& cameraManager)
    : factory_(messageBus, sheetManager, cameraManager, *this)
{}

EntityManager::~EntityManager()
{
    for (const auto& entry : entityMap_) {
        entry.second->Destroy();
    }
}

void EntityManager::DrawTo(sf::RenderTarget& renderTarget) const
{
    for (auto p : drawables_) {
        auto id = p.second.id_;
        entityMap_.at(id)->DrawTo(renderTarget);
    }
}

void EntityManager::Update(float deltaTime)
{
    for (const auto& entry : entityMap_) {
        entry.second->Update(deltaTime);
    }
}

void EntityManager::CreateEntity(const PropertyData& data, const Shared::MapData& mapData)
{
    auto entity = factory_.Create(data.typeStr_, mapData);
    entity->Create(data);
    createdEntities_.push_back(std::move(entity));
}

void EntityManager::CreateEntity(const std::string& typeStr, const sf::Vector2f& pos,
                                 std::unordered_map<std::string, std::string> properties,
                                 const Shared::MapData& mapData)
{
    PropertyData data;
    data.typeStr_ = typeStr;
    data.position_ = pos;
    data.properties_ = properties;
    CreateEntity(data, mapData);
}

void EntityManager::CreateTileEntity(const sf::Vector2f& pos, const Shared::Graphic& graphic,
                                     const Shared::MapData& mapData)
{
    PropertyData data;
    data.typeStr_ = TileEntity::str;
    data.position_ = pos;
    data.graphic_ = graphic;
    CreateEntity(data, mapData);
}

void EntityManager::DeleteEntity(EntityId id)
{
    deletedEntities_.push_back(id);
}

void EntityManager::HandleCreatedEntities()
{
    for (auto& entity : createdEntities_) {
        entity->Init();
        AddDrawable(entity->GetId(), entity->GetLayer());
        AddEntity(std::move(entity));
    }
    createdEntities_.clear();
}

void EntityManager::HandleDeletedEntities()
{
    for (auto id : deletedEntities_) {
        entityMap_[id]->Destroy();
        entityMap_.erase(id);
        RemoveDrawable(id);
    }
    deletedEntities_.clear();
}

void EntityManager::AddEntity(std::unique_ptr<Entity::BasicEntity> entity)
{
    auto id = entity->GetId();
    if (entityMap_.find(id) == entityMap_.end()) {
        entityMap_[id] = std::move(entity);
    }
    else {
        LOG_ERROR("id: %u already exist", id);
    }
}

void EntityManager::AddDrawable(EntityId id, LayerType layer)
{
    std::stringstream ss;
    int l = static_cast<int>(layer);
    ss << l << "_" << id;
    drawables_[ss.str()] = {layer, id};
}

void EntityManager::RemoveDrawable(EntityId id)
{
    auto it = std::find_if(drawables_.begin(), drawables_.end(), [id](const auto& p) { return p.second.id_ == id; });
    if (it != drawables_.end()) {
        drawables_.erase(it);
    }
}

}  // namespace Entity

}  // namespace FA
