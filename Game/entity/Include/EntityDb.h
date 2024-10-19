/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Id.h"

namespace FA {

namespace Entity {

class EntityIf;

class EntityDb
{
public:
    ~EntityDb();

    void AddEntity(std::unique_ptr<EntityIf> entity);
    void DeleteEntity(EntityId id);
    EntityIf& GetEntity(EntityId id) const;

private:
    std::unordered_map<EntityId, std::unique_ptr<EntityIf>> entityMap_;
};

}  // namespace Entity

}  // namespace FA
