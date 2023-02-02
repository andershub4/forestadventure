/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SpawnManager.h"

#include "Entities/BasicEntity.h"
#include "EntityManager.h"
#include "Enum/MoveDirection.h"
#include "Events/StartMoveEvent.h"
#include "PropertyData.h"

namespace FA {

namespace Entity {

SpawnManager::SpawnManager(EntityManager &entityManager)
    : entityManager_(entityManager)
{}

SpawnManager::~SpawnManager() = default;

void SpawnManager::Update(float deltaTime)
{}

void SpawnManager::Spawn(EntityType entityType, const sf::Vector2f &position, const Shared::MapData &mapData,
                         MoveDirection moveDir)
{
    Entity::PropertyData data;
    data.position_ = position;

    auto &entity = entityManager_.CreateEntity(entityType, data, mapData);
    entity.QueueInitEvents(std::make_shared<StartMoveEvent>(moveDir));
}

}  // namespace Entity

}  // namespace FA
