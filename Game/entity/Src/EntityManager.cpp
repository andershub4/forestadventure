/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityManager.h"

#include <memory>

#include "CollisionHandler.h"
#include "DrawHandler.h"
#include "Entities/BasicEntity.h"
#include "EntityDb.h"
#include "EntityLifePool.h"
#include "EntityService.h"
#include "Factory.h"
#include "Logging.h"

namespace FA {

namespace Entity {

EntityManager::EntityManager(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                             const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews)
    : messageBus_(messageBus)
    , textureManager_(textureManager)
    , sheetManager_(sheetManager)
    , cameraViews_(cameraViews)
    , factory_(std::make_unique<Factory>())
    , entityDb_(std::make_unique<EntityDb>())
    , collisionHandler_(std::make_unique<CollisionHandler>(*entityDb_))
    , drawHandler_(std::make_unique<DrawHandler>(*entityDb_))
    , entityLifePool_(std::make_unique<EntityLifePool>())
{}

EntityManager::~EntityManager() = default;

void EntityManager::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    drawHandler_->DrawTo(renderTarget);
}

void EntityManager::DetectCollisions()
{
    collisionHandler_->DetectCollisions();
}

void EntityManager::DetectOutsideTileMap(const sf::Vector2u &mapSize)
{
    collisionHandler_->DetectOutsideTileMap(mapSize);
}

void EntityManager::HandleCollisions()
{
    collisionHandler_->HandleCollisions();
}

void EntityManager::HandleOutsideTileMap()
{
    collisionHandler_->HandleOutsideTileMap();
}

void EntityManager::Update(float deltaTime)
{
    for (const auto id : allEntities_) {
        entityDb_->GetEntity(id).Update(deltaTime);
    }
}

void EntityManager::AddToCreationPool(const Shared::EntityData &entityData)
{
    entityLifePool_->AddToCreationPool(entityData);
}

void EntityManager::AddToDeletionPool(EntityId id)
{
    entityLifePool_->AddToDeletionPool(id);
}

void EntityManager::HandleCreationPool()
{
    auto creationPool = entityLifePool_->MoveCreationPool();
    for (const auto &data : creationPool) {
        HandleCreation(data);
    }
}

void EntityManager::HandleDeletionPool()
{
    auto deletionPool = entityLifePool_->MoveDeletionPool();
    for (const auto &id : deletionPool) {
        HandleDeletion(id);
    }
}

void EntityManager::HandleCreation(const Shared::EntityData &data)
{
    auto service = std::make_unique<EntityService>(messageBus_, textureManager_, sheetManager_, cameraViews_,
                                                   *entityDb_, *entityLifePool_);
    auto entity = factory_->Create(data, std::move(service));
    allEntities_.insert(entity->GetId());
    entity->Init();
    allEntities_.insert(entity->GetId());
    AddDrawable(entity->GetId(), entity->GetLayer());
    collisionHandler_->AddCollider(entity->GetId(), entity->IsStatic());
    entityDb_->AddEntity(std::move(entity));
}

void EntityManager::HandleDeletion(EntityId id)
{
    auto &entity = entityDb_->GetEntity(id);
    entity.Destroy();
    allEntities_.erase(entity.GetId());
    RemoveDrawable(entity.GetId());
    collisionHandler_->RemoveCollider(entity.GetId(), entity.IsStatic());
    entityDb_->DeleteEntity(id);
}

void EntityManager::AddDrawable(EntityId id, LayerType layer)
{
    drawHandler_->AddDrawable(id, layer);
}

void EntityManager::RemoveDrawable(EntityId id)
{
    drawHandler_->RemoveDrawable(id);
}

}  // namespace Entity

}  // namespace FA
