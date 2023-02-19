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

class CameraManager;
class MessageBus;
class SheetManager;
struct MapData;

}  // namespace Shared

namespace Entity {

class EntityManager;
class BasicEntity;
class EntityService;
struct PropertyData;

class Factory
{
public:
    Factory(Shared::MessageBus& messageBus, const Shared::SheetManager& sheetManager,
            const Shared::CameraManager& cameraManager, EntityManager& entityManager);
    ~Factory();

    std::unique_ptr<BasicEntity> Create(const PropertyData& data, const Shared::MapData& mapData) const;

private:
    using CreateFn = std::function<std::unique_ptr<BasicEntity>(EntityId, const PropertyData&, const EntityService&)>;

    mutable EntityId id_{0};
    Shared::MessageBus& messageBus_;
    const Shared::SheetManager& sheetManager_;
    const Shared::CameraManager& cameraManager_;
    EntityManager& entityManager_;
    std::unordered_map<std::string, CreateFn> map_;

private:
    void RegisterEntity(const std::string& typeStr, CreateFn createFn);
};

}  // namespace Entity

}  // namespace FA
