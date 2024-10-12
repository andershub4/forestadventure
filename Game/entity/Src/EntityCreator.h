/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Id.h"
#include "MapData.h"
#include "PropertyData.h"
#include "Resource/TextureManager.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

struct TileGraphic;
class MessageBus;
class SheetManager;
class CameraViews;

}  // namespace Shared

namespace Entity {

class BasicEntity;
class Factory;
class EntityDb;

class EntityCreator
{
public:
    EntityCreator(Shared::MessageBus &messageBus, const Shared::TextureManager &textureManager,
                  const Shared::SheetManager &sheetManager, const Shared::CameraViews &cameraViews,
                  const Factory &factory, EntityDb &entityDb);

    void RegisterOnCreateFn(std::function<void(BasicEntity &)> fn);
    void RegisterOnDeleteFn(std::function<void(BasicEntity &)> fn);
    void CreateEntity(const PropertyData &data, const Shared::MapData &mapData);
    void CreateEntity(const std::string &typeStr, const sf::Vector2f &pos, const sf::Vector2f &size,
                      std::unordered_map<std::string, std::string> properties, const Shared::MapData &mapData);
    void DeleteEntity(EntityId id);
    void HandleCreatedEntities();
    void HandleDeletedEntities();

private:
    Shared::MessageBus &messageBus_;
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    const Shared::CameraViews &cameraViews_;
    const Factory &factory_;
    EntityDb &entityDb_;

    struct CreatedItem
    {
        PropertyData propertyData_;
        Shared::MapData mapData_;
    };

    std::vector<CreatedItem> createdEntities_;
    std::unordered_set<EntityId> deletedEntities_;
    std::function<void(BasicEntity &)> onCreateFn_;
    std::function<void(BasicEntity &)> onDeleteFn_;
};

}  // namespace Entity

}  // namespace FA
