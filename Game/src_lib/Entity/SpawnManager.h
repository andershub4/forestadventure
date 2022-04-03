/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityManager;

class SpawnManager
{
public:
    SpawnManager(EntityManager &entityManager);
    ~SpawnManager();

    void Update(float deltaTime);

    void Spawn(EntityType entityType, const sf::Vector2f &position, FaceDirection faceDir, float rotation);

private:
    EntityManager &entityManager_;
};

}  // namespace Entity

}  // namespace FA
