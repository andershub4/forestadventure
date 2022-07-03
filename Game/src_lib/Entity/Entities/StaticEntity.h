/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class StaticEntity : public BasicEntity
{
public:
    StaticEntity(EntityId id, CameraManager& cameraManager, const SheetManager& textureManager,
                 EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize);
    virtual ~StaticEntity();

    virtual std::string Name() const override { return "StaticEntity"; }
    virtual EntityType Type() const override { return EntityType::Static; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }
};

}  // namespace Entity

}  // namespace FA
