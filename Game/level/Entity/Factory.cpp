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

Factory::Factory(Shared::MessageBus& messageBus, const Shared::SheetManager& sheetManager,
                 const CameraManager& cameraManager, Level& level)
    : messageBus_(messageBus)
    , sheetManager_(sheetManager)
    , cameraManager_(cameraManager)
    , level_(level)
{}

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(EntityType type, const Shared::MapData& mapData) const
{
    EntityService service(messageBus_, sheetManager_, cameraManager_, mapData);

    switch (type) {
        case EntityType::Mole:
            return std::make_unique<MoleEntity>(id_++, level_, service);
            break;
        case EntityType::Player:
            return std::make_unique<PlayerEntity>(id_++, level_, service);
            break;
        case EntityType::Arrow:
            return std::make_unique<ArrowEntity>(id_++, level_, service);
            break;
        case EntityType::Tile:
            return std::make_unique<TileEntity>(id_++, level_, service);
            break;
        case EntityType::Coin:
            return std::make_unique<CoinEntity>(id_++, level_, service);
            break;
        default:
            auto t = static_cast<int>(type);
            LOG_ERROR("Could not create entity of type: %u", t);
            return nullptr;
    }
}

}  // namespace Entity

}  // namespace FA
