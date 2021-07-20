/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Entity/Entities/BasicEntity.h"
#include "Entity/Factory.h"
#include "Entity/Id.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityManager
{
public:
    EntityManager(MessageBus &messageBus, const TextureManager &textureManager);
    ~EntityManager();

    void Update(float deltaTime);
    void LateUpdate();
    void DrawTo(sf::RenderTarget &renderTarget) const;
    void EnableInput(bool enable);
    BasicEntity *Create(const Configuration &configuration);

private:
    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
    MessageBus &messageBus_;
    const TextureManager &textureManager_;
    Factory factory_;

private:
    void AddEntity(std::unique_ptr<Entity::BasicEntity> entity);
};

}  // namespace Entity

}  // namespace FA
