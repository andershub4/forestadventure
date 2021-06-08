/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Factory.h"

#include "Entities/MoleEntity.h"
#include "Entities/PlayerEntity.h"
#include "Logger.h"

namespace FA {

namespace Entity {

Factory::Factory() = default;

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(EntityType type, EntityId id, MessageBus& messageBus) const
{
    switch (type) {
        case EntityType::Mole:
            return std::make_unique<MoleEntity>(id, messageBus);
            break;
        case EntityType::Player:
            return std::make_unique<PlayerEntity>(id, messageBus);
        default:
            auto t = static_cast<int>(type);
            LOG_ERROR("Could not create entity of type: ", t);
            return nullptr;
    }
}

}  // namespace Entity

}  // namespace FA
