/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Entity/Entities/BasicEntity.h"
#include "Entity/Id.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;

namespace Entity {
struct Configuration;
}

class EntitySystem
{
public:
    EntitySystem(MessageBus &messageBus);
    ~EntitySystem();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget) const;
    void Create(AnimationManager &animationManager, TileSet &tileSet, Camera &camera,
                const Entity::Configuration &configuration);
    void EnableInput(bool enable);

private:
    MessageBus &messageBus_;
    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
    Entity::EntityId entityId_ = 0;

private:
    Entity::EntityId GenerateId();
    void AddEntity(Entity::EntityId entityId, std::unique_ptr<Entity::BasicEntity> entity);
};

}  // namespace FA
