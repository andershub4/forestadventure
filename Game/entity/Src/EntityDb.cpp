/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityDb.h"

#include "EntityIf.h"
#include "Logging.h"

namespace FA {

namespace Entity {

EntityDb::~EntityDb()
{
    for (const auto& entry : entityMap_) {
        entry.second->Destroy();
    }
}

void EntityDb::AddEntity(std::unique_ptr<EntityIf> entity)
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
    auto& entity = GetEntity(id);
    entity.Destroy();
    entityMap_.erase(id);
}

EntityIf& EntityDb::GetEntity(EntityId id) const
{
    if (entityMap_.find(id) == entityMap_.end()) {
        LOG_ERROR("%s does not exist", DUMP(id));
    }

    return *entityMap_.at(id);
}

}  // namespace Entity

}  // namespace FA
