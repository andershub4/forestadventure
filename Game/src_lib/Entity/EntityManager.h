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

namespace Entity {

class BasicEntity;
class Factory;
class ComponentHandler;

class EntityManager
{
public:
    EntityManager(const Factory &factory);
    ~EntityManager();

    void Update(float deltaTime);
    void LateUpdate();
    void DrawTo(sf::RenderTarget &renderTarget) const;
    void EnableInput(bool enable);
    BasicEntity *Create(EntityType type, const ComponentHandler &componentHandler);

private:
    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
    const Factory &factory_;

private:
    void AddEntity(std::unique_ptr<Entity::BasicEntity> entity);
};

}  // namespace Entity

}  // namespace FA
