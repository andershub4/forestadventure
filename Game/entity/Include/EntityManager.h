/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <unordered_map>

#include "Id.h"
#include "LayerType.h"
#include "Resource/TextureManager.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class IRenderTarget;

}  // namespace Graphic

namespace Shared {

struct MapData;
struct TileGraphic;
class MessageBus;
class SheetManager;
class CameraViews;

}  // namespace Shared

namespace Entity {

class BasicEntity;
class Factory;
class EntityService;
struct PropertyData;

class EntityManager
{
public:
    EntityManager(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                  const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews);
    ~EntityManager();

    void Update(float deltaTime);
    void DrawTo(Graphic::IRenderTarget &renderTarget) const;
    void CreateEntity(const PropertyData &data, const Shared::MapData &mapData);
    void CreateEntity(const std::string &typeStr, const sf::Vector2f &pos,
                      std::unordered_map<std::string, std::string> properties, const Shared::MapData &mapData);
    void CreateTileEntity(const sf::Vector2f &pos, const Shared::TileGraphic &graphic, const Shared::MapData &mapData);
    void DeleteEntity(EntityId id);
    void HandleCreatedEntities();
    void HandleDeletedEntities();

private:
    struct DrawableInfo
    {
        LayerType layer_{};
        EntityId id_{};
    };

    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
    std::unique_ptr<Factory> factory_;
    std::unique_ptr<EntityService> service_;
    std::vector<std::unique_ptr<BasicEntity>> createdEntities_;
    std::vector<EntityId> deletedEntities_;
    std::map<std::string, DrawableInfo> drawables_;

private:
    void AddEntity(std::unique_ptr<Entity::BasicEntity> entity);
    void AddDrawable(EntityId id, LayerType layer);
    void RemoveDrawable(EntityId id);
};

}  // namespace Entity

}  // namespace FA
