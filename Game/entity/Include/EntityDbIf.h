/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Id.h"

namespace FA {

namespace Entity {

class EntityIf;

class EntityDbIf
{
public:
    virtual ~EntityDbIf() = default;

    virtual void AddEntity(std::unique_ptr<EntityIf> entity) = 0;
    virtual void DeleteEntity(EntityId id) = 0;
    virtual EntityIf& GetEntity(EntityId id) const = 0;

protected:
    EntityDbIf() = default;
    EntityDbIf(const EntityDbIf&) = default;
    EntityDbIf(EntityDbIf&&) = default;
    EntityDbIf& operator=(const EntityDbIf&) = default;
    EntityDbIf& operator=(EntityDbIf&&) = default;
};

}  // namespace Entity

}  // namespace FA
