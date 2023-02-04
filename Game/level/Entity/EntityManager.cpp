/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <sstream>

#include "EntityManager.h"

#include "Entity/Entities/BasicEntity.h"
#include "Logging.h"

namespace FA {

namespace Entity {

EntityManager::EntityManager(Shared::MessageBus& messageBus, const Shared::SheetManager& sheetManager,
                             const CameraManager& cameraManager)
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

void EntityManager::CreateEntity(const std::string& typeStr, const PropertyData& data, const Shared::MapData& mapData)
{
    auto entity = factory_.Create(typeStr, mapData);
    entity->Create(data);
    createdEntities_.push_back(std::move(entity));
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

void EntityManager::Init()
{
    for (const auto& entry : entityMap_) {
        entry.second->Init();
    }
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
