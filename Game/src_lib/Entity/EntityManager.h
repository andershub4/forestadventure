/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Entity/Id.h"
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
    void EnableInput(bool enable);
    void Create(EntityType type, const PropertyData &data);
    void Init(); 

private:
    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
    const Factory &factory_;
    CameraManager &cameraManager_;
    const SheetManager &sheetManager_;

private:
    void AddEntity(std::unique_ptr<Entity::BasicEntity> entity);
};

}  // namespace Entity

}  // namespace FA
