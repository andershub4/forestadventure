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

namespace Entity {

class BasicEntity;
class EntityService;
struct PropertyData;

class Factory
{
public:
    Factory();
    ~Factory();

    std::unique_ptr<BasicEntity> Create(const PropertyData& data, std::unique_ptr<EntityService> service) const;

private:
    using CreateFn =
        std::function<std::unique_ptr<BasicEntity>(EntityId, const PropertyData&, std::unique_ptr<EntityService>)>;

    mutable EntityId id_{0};
    std::unordered_map<std::string, CreateFn> map_;

private:
    void RegisterEntity(const std::string& typeStr, CreateFn createFn);
};

}  // namespace Entity

}  // namespace FA
