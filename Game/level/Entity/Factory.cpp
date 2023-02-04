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
                 const CameraManager& cameraManager, EntityManager& entityManager)
    : messageBus_(messageBus)
    , sheetManager_(sheetManager)
    , cameraManager_(cameraManager)
    , entityManager_(entityManager)
{}

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(const std::string& typeStr, const Shared::MapData& mapData) const
{
    EntityService service(messageBus_, sheetManager_, cameraManager_, entityManager_, mapData);

    if (typeStr == "Mole") {
        return std::make_unique<MoleEntity>(id_++, service);
    }
    else if (typeStr == "Player") {
        return std::make_unique<PlayerEntity>(id_++, service);
    }
    else if (typeStr == "Arrow") {
        return std::make_unique<ArrowEntity>(id_++, service);
    }
    else if (typeStr == "Tile") {
        return std::make_unique<TileEntity>(id_++, service);
    }
    else if (typeStr == "Coin") {
        return std::make_unique<CoinEntity>(id_++, service);
    }

    LOG_ERROR("Could not create entity of type: %s", typeStr.c_str());
    return nullptr;
}

}  // namespace Entity

}  // namespace FA
