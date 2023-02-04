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
{
    RegisterEntity("Mole", [](EntityId id, const EntityService& s) { return std::make_unique<MoleEntity>(id, s); });
    RegisterEntity("Player", [](EntityId id, const EntityService& s) { return std::make_unique<PlayerEntity>(id, s); });
    RegisterEntity("Arrow", [](EntityId id, const EntityService& s) { return std::make_unique<ArrowEntity>(id, s); });
    RegisterEntity("Tile", [](EntityId id, const EntityService& s) { return std::make_unique<TileEntity>(id, s); });
    RegisterEntity("Coin", [](EntityId id, const EntityService& s) { return std::make_unique<CoinEntity>(id, s); });
}

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(const std::string& typeStr, const Shared::MapData& mapData) const
{
    auto it = map_.find(typeStr);

    if (it != map_.end()) {
        EntityService service(messageBus_, sheetManager_, cameraManager_, entityManager_, mapData);
        return it->second(id_++, service);
    }

    LOG_ERROR("Could not create entity of type: %s", typeStr.c_str());
    return nullptr;
}

void Factory::RegisterEntity(const std::string& typeStr, Factory::CreateFn createFn)
{
    map_[typeStr] = createFn;
}

}  // namespace Entity

}  // namespace FA
