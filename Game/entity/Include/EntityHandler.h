/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_set>

#include "Id.h"
#include "Resource/TextureManager.h"

namespace FA {

namespace Shared {

class MessageBus;
struct EntityData;
class SheetManager;
class CameraViews;

}  // namespace Shared

namespace Entity {

class EntityDb;
class Factory;
class EntityLifeHandler;

class EntityHandler
{
public:
    EntityHandler(EntityDb &entityDb);
    ~EntityHandler();

    void Update(float deltaTime);
    EntityId AddEntity(const Shared::EntityData &data, const Factory &factory, Shared::MessageBus &messageBus,
                       const Shared::TextureManager &textureManager, const Shared::SheetManager &sheetManager,
                       const Shared::CameraViews &cameraViews, EntityLifeHandler &entityLifeHandler);
    void RemoveEntity(EntityId id);

private:
    EntityDb &entityDb_;
    std::unordered_set<Entity::EntityId> allEntities_;
};

}  // namespace Entity

}  // namespace FA
