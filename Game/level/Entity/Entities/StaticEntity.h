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
    StaticEntity(EntityId id, Level& level, const SheetManager& textureManager, MessageBus& messageBus);
    virtual ~StaticEntity();

    virtual std::string Name() const override { return "StaticEntity"; }
    virtual EntityType Type() const override { return EntityType::Static; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }
};

}  // namespace Entity

}  // namespace FA
