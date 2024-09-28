/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <sstream>

#include "EntityManager.h"

#include "Entities/BasicEntity.h"
#include "Entities/TileEntity.h"
#include "EntityService.h"
#include "Factory.h"
#include "Logging.h"
#include "PropertyData.h"

namespace FA {

namespace Entity {

EntityManager::EntityManager(Shared::MessageBus& messageBus, const Shared::TextureManager& textureManager,
                             const Shared::SheetManager& sheetManager, const Shared::CameraViews& cameraViews)
    : factory_(std::make_unique<Factory>())
    , service_(std::make_unique<EntityService>(messageBus, textureManager, sheetManager, cameraViews, *this))
{}

EntityManager::~EntityManager()
{
    for (const auto& entry : entityMap_) {
        entry.second->Destroy();
    }
}

void EntityManager::DrawTo(Graphic::RenderTargetIf& renderTarget) const
{
    for (auto p : drawables_) {
        auto id = p.second.id_;
        entityMap_.at(id)->DrawTo(renderTarget);
    }
}

void EntityManager::DetectCollisions()
{
    for (const auto id : entities_) {
        DetectEntityCollisions(id);
        DetectStaticCollisions(id);
    }
}

void EntityManager::DetectEntityCollisions(EntityId id)
{
    for (const auto otherId : entities_) {
        if (id != otherId) {
            DetectCollision(id, otherId);
        }
    }
}

void EntityManager::DetectStaticCollisions(EntityId id)
{
    for (const auto otherId : staticEntities_) {
        DetectCollision(id, otherId);
    }
}

void EntityManager::DetectCollision(EntityId id, EntityId otherId)
{
    std::pair<EntityId, EntityId> pair{id, otherId};
    bool found = collisionPairs_.find(pair) != collisionPairs_.end();
    if (!found) {
        const auto& entity = *entityMap_.at(id);
        const auto& otherEntity = *entityMap_.at(otherId);
        bool intersect = entity.Intersect(otherEntity);
        if (intersect) {
            collisionPairs_.insert(pair);
        }
    }
}

void EntityManager::HandleCollisions()
{
    for (const auto& pair : collisionPairs_) {
        auto& first = *entityMap_.at(pair.first);
        auto& second = *entityMap_.at(pair.second);
        first.HandleCollision(pair.second, entityMap_.at(pair.second)->IsSolid());
        second.HandleCollision(pair.first, entityMap_.at(pair.first)->IsSolid());
    }
    collisionPairs_.clear();
}

EntityType EntityManager::GetType(EntityId id) const
{
    return entityMap_.at(id)->Type();
}

void EntityManager::Update(float deltaTime)
{
    for (const auto& entry : entityMap_) {
        entry.second->Update(deltaTime);
    }
}

void EntityManager::CreateEntity(const PropertyData& data, const Shared::MapData& mapData)
{
    auto entity = factory_->Create(data, mapData, *service_);
    auto id = entity->GetId();
    createdEntities_.push_back(id);
    AddEntity(std::move(entity));
}

void EntityManager::CreateEntity(const std::string& typeStr, const sf::Vector2f& pos, const sf::Vector2f& size,
                                 std::unordered_map<std::string, std::string> properties,
                                 const Shared::MapData& mapData)
{
    PropertyData data;
    data.typeStr_ = typeStr;
    data.position_ = pos;
    data.size_ = size;
    data.properties_ = properties;
    CreateEntity(data, mapData);
}

void EntityManager::CreateTileEntity(const sf::Vector2f& pos, const Shared::TileGraphic& graphic,
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
    if (std::find(deletedEntities_.begin(), deletedEntities_.end(), id) != deletedEntities_.end()) {
        LOG_WARN("%s is already ready to be deleted", DUMP(id));
    }
    deletedEntities_.push_back(id);
}

void EntityManager::HandleCreatedEntities()
{
    for (const auto id : createdEntities_) {
        auto& entity = *entityMap_.at(id);
        entity.Init();
        AddDrawable(id, entity.GetLayer());
        if (entity.IsStatic()) {
            staticEntities_.push_back(id);
        }
        else {
            entities_.push_back(id);
        }
    }

    createdEntities_.clear();
}

void EntityManager::HandleDeletedEntities()
{
    for (auto id : deletedEntities_) {
        entityMap_[id]->Destroy();
        entityMap_.erase(id);
        RemoveDrawable(id);
        RemoveEntity(id);
        RemoveStaticEntity(id);
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
        LOG_ERROR("%s already exist", DUMP(id));
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

void EntityManager::RemoveEntity(EntityId id)
{
    auto it = std::find_if(entities_.begin(), entities_.end(), [id](const auto& p) { return p == id; });
    if (it != entities_.end()) {
        entities_.erase(it);
    }
}

void EntityManager::RemoveStaticEntity(EntityId id)
{
    auto it = std::find_if(staticEntities_.begin(), staticEntities_.end(), [id](const auto& p) { return p == id; });
    if (it != staticEntities_.end()) {
        staticEntities_.erase(it);
    }
}

}  // namespace Entity

}  // namespace FA
