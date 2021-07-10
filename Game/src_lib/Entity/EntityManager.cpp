#include "EntityManager.h"

#include "Logging.h"

namespace FA {

namespace Entity {

EntityManager::EntityManager() = default;

EntityManager::~EntityManager()
{
    for (const auto& entry : entityMap_) {
        entry.second->OnDestroy();
    }
}

void EntityManager::DrawTo(sf::RenderTarget& renderTarget) const
{
    for (const auto& entry : entityMap_) {
        entry.second->DrawTo(renderTarget);
    }
}

void EntityManager::Update(float deltaTime)
{
    for (const auto& entry : entityMap_) {
        entry.second->Update(deltaTime);
    }
}

void EntityManager::LateUpdate()
{
    for (const auto& entry : entityMap_) {
        entry.second->LateUpdate();
    }
}

void EntityManager::AddEntity(std::unique_ptr<Entity::BasicEntity> entity)
{
    auto id = entity->GetId();
    if (entityMap_.find(id) == entityMap_.end()) {
        entityMap_[id] = std::move(entity);
    }
    else {
        LOG_ERROR("id: ", id, " already exist");
    }
}

void EntityManager::EnableInput(bool enable)
{
    for (const auto& entry : entityMap_) {
        entry.second->EnableInput(enable);
    }
}

}  // namespace Entity

}  // namespace FA
