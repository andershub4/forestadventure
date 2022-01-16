/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Factory.h"

#include "Entities/ArrowEntity.h"
#include "Entities/MoleEntity.h"
#include "Entities/PlayerEntity.h"
#include "Logging.h"

namespace FA {

namespace Entity {

Factory::Factory(MessageBus& messageBus)
    : messageBus_(messageBus)
{}

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(EntityType type, CameraManager& cameraManager,
                                             const SheetManager& sheetManager, EntityManager& entityManager) const
{
    switch (type) {
        case EntityType::Mole:
            return std::make_unique<MoleEntity>(id_++, cameraManager, sheetManager, entityManager, messageBus_);
            break;
        case EntityType::Player:
            return std::make_unique<PlayerEntity>(id_++, cameraManager, sheetManager, entityManager, messageBus_);
            break;
        case EntityType::Arrow:
            return std::make_unique<ArrowEntity>(id_++, cameraManager, sheetManager, entityManager, messageBus_);
            break;
        default:
            auto t = static_cast<int>(type);
            LOG_ERROR("Could not create entity of type: ", t);
            return nullptr;
    }
}

}  // namespace Entity

}  // namespace FA
