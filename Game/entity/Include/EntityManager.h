/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_set>

#include "Id.h"
#include "LayerType.h"
#include "Resource/TextureManager.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

struct EntityData;
class MessageBus;
class SheetManager;
class CameraViews;

}  // namespace Shared

namespace Entity {

class BasicEntity;
class Factory;
class EntityDb;
class EntityLifePool;
class CollisionHandler;
class DrawHandler;

class EntityManager
{
public:
    EntityManager(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                  const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews);
    ~EntityManager();

    void Update(float deltaTime);
    void DrawTo(Graphic::RenderTargetIf &renderTarget) const;
    void DetectCollisions();
    void DetectOutsideTileMap(const sf::Vector2u &mapSize);
    void HandleCollisions();
    void HandleOutsideTileMap();
    void AddToCreationPool(const Shared::EntityData &entityData);
    void AddToDeletionPool(EntityId id);
    void HandleCreationPool();
    void HandleDeletionPool();

private:
    std::unordered_set<EntityId> allEntities_;
    Shared::MessageBus &messageBus_;
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    const Shared::CameraViews &cameraViews_;
    std::unique_ptr<Factory> factory_;
    std::unique_ptr<EntityDb> entityDb_;
    std::unique_ptr<CollisionHandler> collisionHandler_;
    std::unique_ptr<DrawHandler> drawHandler_;
    std::unique_ptr<EntityLifePool> entityLifePool_;

private:
    void AddDrawable(EntityId id, LayerType layer);
    void RemoveDrawable(EntityId id);
    void HandleCreation(const Shared::EntityData &data);
    void HandleDeletion(EntityId id);
};

}  // namespace Entity

}  // namespace FA
