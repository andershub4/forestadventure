#include "EntitySystem.h"

#include "Utils/Logger.h"

namespace FA {

EntitySystem::EntitySystem() = default;

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

void EntitySystem::EnableInput(bool enable)
{
    for (const auto& entry : entityMap_) {
        entry.second->EnableInput(enable);
    }
}

}  // namespace FA
