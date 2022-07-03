/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Factory.h"

#include "Entities/ArrowEntity.h"
#include "Entities/CoinEntity.h"
#include "Entities/MoleEntity.h"
#include "Entities/PlayerEntity.h"
#include "Entities/TileEntity.h"
#include "Logging.h"

namespace FA {

namespace Entity {

Factory::Factory(MessageBus& messageBus, const SheetManager& sheetManager, CameraManager& cameraManager,
                 const sf::Vector2u& mapSize)
    : messageBus_(messageBus)
    , sheetManager_(sheetManager)
    , cameraManager_(cameraManager)
    , mapSize_(mapSize)
{}

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(EntityType type, EntityManager& entityManager) const
{
    switch (type) {
        case EntityType::Mole:
            return std::make_unique<MoleEntity>(id_++, cameraManager_, sheetManager_, entityManager, messageBus_,
                                                mapSize_);
            break;
        case EntityType::Player:
            return std::make_unique<PlayerEntity>(id_++, cameraManager_, sheetManager_, entityManager, messageBus_,
                                                  mapSize_);
            break;
        case EntityType::Arrow:
            return std::make_unique<ArrowEntity>(id_++, cameraManager_, sheetManager_, entityManager, messageBus_,
                                                 mapSize_);
            break;
        case EntityType::Tile:
            return std::make_unique<TileEntity>(id_++, cameraManager_, sheetManager_, entityManager, messageBus_,
                                                mapSize_);
            break;
        case EntityType::Coin:
            return std::make_unique<CoinEntity>(id_++, cameraManager_, sheetManager_, entityManager, messageBus_,
                                                mapSize_);
            break;
        default:
            auto t = static_cast<int>(type);
            LOG_ERROR("Could not create entity of type: ", t);
            return nullptr;
    }
}

}  // namespace Entity

}  // namespace FA
