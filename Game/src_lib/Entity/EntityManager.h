/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <unordered_map>

#include "Entity/Id.h"
#include "Entity/LayerId.h"
#include "Enum/EntityType.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class CameraManager;
class SheetManager;

namespace Entity {

class BasicEntity;
class Factory;
struct PropertyData;

class EntityManager
{
public:
    EntityManager(const Factory &factory, CameraManager &cameraManager, const SheetManager &sheetManager);
    ~EntityManager();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget) const;
    BasicEntity &CreateEntity(EntityType type, const PropertyData &data);
    void DeleteEntity(EntityId id);
    void HandleCreatedEntities();
    void HandleDeletedEntities();
    void Init();

private:
    struct DrawableInfo
    {
        LayerType layer_{};
        EntityId id_{};
    };

    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
    const Factory &factory_;
    CameraManager &cameraManager_;
    const SheetManager &sheetManager_;
    std::vector<std::unique_ptr<BasicEntity>> createdEntities_;
    std::vector<EntityId> deletedEntities_;
    std::map<std::string, DrawableInfo> drawables_;

private:
    void AddEntity(std::unique_ptr<Entity::BasicEntity> entity);
    void AddDrawable(EntityId id, LayerType layerId);
    void RemoveDrawable(EntityId id);
};

}  // namespace Entity

}  // namespace FA
