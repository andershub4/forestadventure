/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "Id.h"
#include "LayerType.h"
#include "Resource/TextureManager.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

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
enum class EntityType;

class EntityManager
{
public:
    EntityManager(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                  const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews);
    ~EntityManager();

    void Update(float deltaTime);
    void DrawTo(Graphic::RenderTargetIf &renderTarget) const;
    void DetectCollisions();
    void DetectStaticCollisions();
    void HandleCollisions();
    EntityType GetType(EntityId id) const;
    void CreateEntity(const PropertyData &data, const Shared::MapData &mapData);
    void CreateEntity(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
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

    template <typename T>
    struct customPairLess
    {
        bool operator()(const std::pair<T, T> &lhs, const std::pair<T, T> &rhs) const
        {
            const auto lhs_order = lhs.first < lhs.second ? lhs : std::tie(lhs.second, lhs.first);
            const auto rhs_order = rhs.first < rhs.second ? rhs : std::tie(rhs.second, rhs.first);

            return lhs_order < rhs_order;
        }
    };

    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
    std::vector<EntityId> entities_;
    std::vector<EntityId> staticEntities_;
    std::unique_ptr<Factory> factory_;
    std::unique_ptr<EntityService> service_;
    std::vector<std::unique_ptr<BasicEntity>> createdEntities_;
    std::vector<std::unique_ptr<BasicEntity>> createdStaticEntities_;
    std::vector<EntityId> deletedEntities_;
    std::map<std::string, DrawableInfo> drawables_;
    std::set<std::pair<EntityId, EntityId>, customPairLess<EntityId>> collisionPairs_;

private:
    void AddEntity(std::unique_ptr<Entity::BasicEntity> entity);
    void AddDrawable(EntityId id, LayerType layer);
    void RemoveDrawable(EntityId id);
    void RemoveEntity(EntityId id);
    void RemoveStaticEntity(EntityId id);
};

}  // namespace Entity

}  // namespace FA
