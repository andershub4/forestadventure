/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Enum/EntityType.h"
#include "Id.h"

namespace FA {

class MessageBus;

namespace Entity {

class BasicEntity;

class Factory
{
public:
    Factory();
    ~Factory();

    std::unique_ptr<BasicEntity> Create(EntityType type, EntityId id, MessageBus& messageBus) const;
};

}  // namespace Entity

}  // namespace FA
