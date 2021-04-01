#include "EntitySystem.h"

#include "Entity/Configuration.h"
#include "Entity/Entities/MoleEntity.h"
#include "Entity/Entities/PlayerEntity.h"
#include "Entity/Entities/StaticEntity.h"
#include "Level/Camera.h"
#include "Message/MessageBus.h"
#include "Resource/AnimationManager.h"
#include "Resource/TileSet.h"
#include "Tile/TileMap.h"
#include "Utils/Logger.h"

namespace FA {

EntitySystem::EntitySystem(MessageBus& messageBus)
    : messageBus_(messageBus)
{}

EntitySystem::~EntitySystem()
{
    for (const auto& entry : entityMap_) {
        entry.second->OnDestroy();
    }
}

void EntitySystem::DrawTo(sf::RenderTarget& renderTarget) const
{
    for (const auto& entry : entityMap_) {
        entry.second->DrawTo(renderTarget);
    }
}

void EntitySystem::Update(float deltaTime)
{
    for (const auto& entry : entityMap_) {
        entry.second->Update(deltaTime);
    }
}

void EntitySystem::AddEntity(Entity::EntityId entityId, std::unique_ptr<Entity::BasicEntity> entity)
{
    if (entityMap_.find(entityId) == entityMap_.end()) {
        entityMap_[entityId] = std::move(entity);
    }
    else {
        LOG_ERROR("entityId: ", entityId, " already exist");
    }
}

void EntitySystem::Create(AnimationManager& animationManager, TileSet& tileSet, Camera& camera,
                          const Entity::Configuration& configuration)
{
    auto type = configuration.entityType_;
    std::unique_ptr<Entity::BasicEntity> entity = nullptr;

    if (type == EntityType::Player) {
        auto id = GenerateId();
        entity = std::make_unique<Entity::PlayerEntity>(id, messageBus_);
        entity->OnCreate(animationManager, tileSet, camera, configuration);
        AddEntity(id, std::move(entity));
    }
    else if (type == EntityType::Mole) {
        auto id = GenerateId();
        entity = std::make_unique<Entity::MoleEntity>(id, messageBus_);
        entity->OnCreate(animationManager, tileSet, camera, configuration);
        AddEntity(id, std::move(entity));
    }
    else if (type == EntityType::Static) {
        auto id = GenerateId();
        entity = std::make_unique<Entity::StaticEntity>(id, messageBus_);
        entity->OnCreate(animationManager, tileSet, camera, configuration);
        AddEntity(id, std::move(entity));
    }
}

void EntitySystem::EnableInput(bool enable)
{
    for (const auto& entry : entityMap_) {
        entry.second->EnableInput(enable);
    }
}

Entity::EntityId EntitySystem::GenerateId()
{
    return entityId_++;
}

}  // namespace FA
