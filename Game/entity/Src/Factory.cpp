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
                 const Shared::CameraManager& cameraManager, EntityManager& entityManager)
    : messageBus_(messageBus)
    , sheetManager_(sheetManager)
    , cameraManager_(cameraManager)
    , entityManager_(entityManager)
{
    RegisterEntity(MoleEntity::str, [](EntityId id, const PropertyData& data, const EntityService& s) {
        return std::make_unique<MoleEntity>(id, data, s);
    });
    RegisterEntity(PlayerEntity::str, [](EntityId id, const PropertyData& data, const EntityService& s) {
        return std::make_unique<PlayerEntity>(id, data, s);
    });
    RegisterEntity(ArrowEntity::str, [](EntityId id, const PropertyData& data, const EntityService& s) {
        return std::make_unique<ArrowEntity>(id, data, s);
    });
    RegisterEntity(TileEntity::str, [](EntityId id, const PropertyData& data, const EntityService& s) {
        return std::make_unique<TileEntity>(id, data, s);
    });
    RegisterEntity(CoinEntity::str, [](EntityId id, const PropertyData& data, const EntityService& s) {
        return std::make_unique<CoinEntity>(id, data, s);
    });
}

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(const PropertyData& data, const Shared::MapData& mapData) const
{
    auto it = map_.find(data.typeStr_);

    if (it != map_.end()) {
        EntityService service(messageBus_, sheetManager_, cameraManager_, entityManager_, mapData);
        return it->second(id_++, data, service);
    }

    LOG_ERROR("Could not create entity of type: %s", data.typeStr_.c_str());
    return nullptr;
}

void Factory::RegisterEntity(const std::string& typeStr, Factory::CreateFn createFn)
{
    map_[typeStr] = createFn;
}

}  // namespace Entity

}  // namespace FA
