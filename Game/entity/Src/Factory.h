/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Id.h"

namespace FA {

namespace Shared {

struct EntityData;

}  // namespace Shared

namespace Entity {

class BasicEntity;
class EntityService;

class Factory
{
public:
    Factory();
    ~Factory();

    std::unique_ptr<BasicEntity> Create(const Shared::EntityData& data, std::unique_ptr<EntityService> service) const;

private:
    using CreateFn = std::function<std::unique_ptr<BasicEntity>(EntityId, const Shared::EntityData&,
                                                                std::unique_ptr<EntityService>)>;

    mutable EntityId id_{0};
    std::unordered_map<std::string, CreateFn> map_;

private:
    void RegisterEntity(const std::string& typeStr, CreateFn createFn);
};

}  // namespace Entity

}  // namespace FA
