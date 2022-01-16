/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

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

    void SpawnArrow(const sf::Vector2f &position, FaceDirection faceDir, float scale, float velocity);

private:
    EntityManager &entityManager_;
};

}  // namespace Entity

}  // namespace FA
