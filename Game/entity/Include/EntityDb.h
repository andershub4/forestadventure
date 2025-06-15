/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "EntityDbIf.h"
#include "Id.h"

namespace FA {

namespace Entity {

class EntityIf;

class EntityDb : public EntityDbIf
{
public:
    ~EntityDb();

    virtual void AddEntity(std::unique_ptr<EntityIf> entity) override;
    virtual void DeleteEntity(EntityId id) override;
    virtual EntityIf& GetEntity(EntityId id) const override;

private:
    std::unordered_map<EntityId, std::unique_ptr<EntityIf>> entityMap_;
};

}  // namespace Entity

}  // namespace FA
