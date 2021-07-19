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
    StaticEntity(EntityId id, MessageBus& messageBus);
    virtual ~StaticEntity();

    virtual std::string Name() const override { return "StaticEntity"; }
};

}  // namespace Entity

}  // namespace FA
