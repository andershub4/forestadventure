/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <unordered_map>

#include "Entity/Factory.h"
#include "Entity/Id.h"
#include "Entity/LayerType.h"

#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Shared {

struct MapData;
struct Graphic;

}  // namespace Shared

namespace Entity {

class BasicEntity;
class Factory;
struct PropertyData;

class EntityManager
{
public:
    EntityManager(Shared::MessageBus &messageBus, const Shared::SheetManager &sheetManager,
                  const Shared::CameraManager &cameraManager);
    ~EntityManager();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget) const;
    void CreateEntity(const PropertyData &data, const Shared::MapData &mapData);
    void CreateEntity(const std::string &typeStr, const sf::Vector2f &pos,
                      std::unordered_map<std::string, std::string> properties, const Shared::MapData &mapData);
    void CreateTileEntity(const sf::Vector2f &pos, const Shared::Graphic &graphic, const Shared::MapData &mapData);
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
    Factory factory_;
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
