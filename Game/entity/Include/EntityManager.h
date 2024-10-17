/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <unordered_map>
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

struct TileGraphic;
class MessageBus;
class SheetManager;
class CameraViews;

}  // namespace Shared

namespace Entity {

class BasicEntity;
class Factory;
struct PropertyData;
class EntityDb;
class EntityLifeQueue;
class CollisionHandler;

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
    void AddToCreationQueue(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                            std::unordered_map<std::string, std::string> properties);
    void AddToDeletionQueue(EntityId id);
    void HandleCreationQueue();
    void HandleDeletionQueue();

private:
    struct DrawableInfo
    {
        LayerType layer_{};
        EntityId id_{};
    };

    std::unordered_set<EntityId> allEntities_;
    Shared::MessageBus &messageBus_;
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    const Shared::CameraViews &cameraViews_;
    std::unique_ptr<Factory> factory_;
    std::unique_ptr<EntityDb> entityDb_;
    std::unique_ptr<CollisionHandler> collisionHandler_;
    std::unique_ptr<EntityLifeQueue> entityLifeQueue_;
    std::map<std::string, DrawableInfo> drawables_;

private:
    void AddDrawable(EntityId id, LayerType layer);
    void RemoveDrawable(EntityId id);
};

}  // namespace Entity

}  // namespace FA
