/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "Enum/EntityType.h"
#include "Id.h"

namespace FA {

class MessageBus;
class CameraManager;
class SheetManager;

namespace Entity {

class BasicEntity;
class EntityManager;

class Factory
{
public:
    Factory(MessageBus& messageBus, const SheetManager& sheetManager, CameraManager& cameraManager,
            const sf::Vector2u& mapSize);
    ~Factory();

    std::unique_ptr<BasicEntity> Create(EntityType type, EntityManager& entityManager) const;

private:
    mutable Entity::EntityId id_{0};
    MessageBus& messageBus_;
    const SheetManager& sheetManager_;
    CameraManager& cameraManager_;
    sf::Vector2u mapSize_{};
};

}  // namespace Entity

}  // namespace FA
