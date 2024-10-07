/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <sstream>

#include "EntityManager.h"

#include "CollisionHandler.h"
#include "Entities/BasicEntity.h"
#include "Entities/TileEntity.h"
#include "EntityCreator.h"
#include "EntityDb.h"
#include "EntityService.h"
#include "Factory.h"
#include "Logging.h"
#include "PropertyData.h"

namespace FA {

namespace Entity {

EntityManager::EntityManager(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                             const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews)
    : factory_(std::make_unique<Factory>())
    , entityDb_(std::make_unique<EntityDb>())
    , collisionHandler_(std::make_unique<CollisionHandler>(*entityDb_))
    , entityCreator_(std::make_unique<EntityCreator>(*entityDb_))
    , service_(std::make_unique<EntityService>(messageBus, textureManager, sheetManager, cameraViews, *entityDb_,
                                               *entityCreator_))
{
    entityCreator_->RegisterOnCreateFn([this](const BasicEntity &entity) {
        allEntities_.insert(entity.GetId());
        AddDrawable(entity.GetId(), entity.GetLayer());
        collisionHandler_->AddCollider(entity.GetId(), entity.IsStatic());
    });
    entityCreator_->RegisterOnDeleteFn([this](const BasicEntity &entity) {
        allEntities_.erase(entity.GetId());
        RemoveDrawable(entity.GetId());
        collisionHandler_->RemoveCollider(entity.GetId(), entity.IsStatic());
    });
}

EntityManager::~EntityManager() = default;

void EntityManager::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    for (auto p : drawables_) {
        auto id = p.second.id_;
        entityDb_->GetEntity(id).DrawTo(renderTarget);
    }
}

void EntityManager::DetectCollisions()
{
    collisionHandler_->DetectCollisions();
}
void EntityManager::HandleCollisions()
{
    collisionHandler_->HandleCollisions();
}

EntityType EntityManager::GetType(EntityId id) const
{
    return entityDb_->GetEntity(id).Type();
}

void EntityManager::Update(float deltaTime)
{
    for (const auto id : allEntities_) {
        entityDb_->GetEntity(id).Update(deltaTime);
    }
}

void EntityManager::CreateEntity(const PropertyData &data, const Shared::MapData &mapData)
{
    entityCreator_->CreateEntity(data, mapData);
}

void EntityManager::CreateEntity(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                                 std::unordered_map<std::string, std::string> properties,
                                 const Shared::MapData &mapData)
{
    entityCreator_->CreateEntity(typeStr, pos, size, properties, mapData);
}

void EntityManager::CreateTileEntity(const sf::Vector2f &pos, const Shared::TileGraphic &graphic,
                                     const Shared::MapData &mapData)
{
    entityCreator_->CreateTileEntity(pos, graphic, mapData);
}

void EntityManager::DeleteEntity(EntityId id)
{
    entityCreator_->DeleteEntity(id);
}

void EntityManager::HandleCreatedEntities()
{
    entityCreator_->HandleCreatedEntities(*factory_, *service_);
}

void EntityManager::HandleDeletedEntities()
{
    entityCreator_->HandleDeletedEntities();
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
    auto it = std::find_if(drawables_.begin(), drawables_.end(), [id](const auto &p) { return p.second.id_ == id; });
    if (it != drawables_.end()) {
        drawables_.erase(it);
    }
}

}  // namespace Entity

}  // namespace FA
