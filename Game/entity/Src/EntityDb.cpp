/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityDb.h"

#include "Entities/BasicEntity.h"
#include "Logging.h"

namespace FA {

namespace Entity {

EntityDb::~EntityDb()
{
    for (const auto& entry : entityMap_) {
        entry.second->Destroy();
    }
}

void EntityDb::AddEntity(std::unique_ptr<Entity::BasicEntity> entity)
{
    auto id = entity->GetId();
    if (entityMap_.find(id) == entityMap_.end()) {
        entityMap_[id] = std::move(entity);
    }
    else {
        LOG_ERROR("%s already exist", DUMP(id));
    }
}

void EntityDb::DeleteEntity(EntityId id)
{
    entityMap_.erase(id);
}

BasicEntity& EntityDb::GetEntity(EntityId id) const
{
    return *entityMap_.at(id);
}

}  // namespace Entity

}  // namespace FA
