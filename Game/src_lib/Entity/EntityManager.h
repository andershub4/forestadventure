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

namespace Entity {

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void Update(float deltaTime);
    void LateUpdate();
    void DrawTo(sf::RenderTarget &renderTarget) const;
    void EnableInput(bool enable);
    void AddEntity(Entity::EntityId entityId, std::unique_ptr<Entity::BasicEntity> entity);

private:
    std::unordered_map<Entity::EntityId, std::unique_ptr<Entity::BasicEntity>> entityMap_;
};

}  // namespace Entity

}  // namespace FA
