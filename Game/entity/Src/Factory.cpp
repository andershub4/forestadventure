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
#include "Entities/RectEntity.h"
#include "Logging.h"

namespace FA {

namespace Entity {

Factory::Factory()
{
    RegisterEntity(MoleEntity::str, [](EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                                       std::unique_ptr<EntityService> s) {
        return std::make_unique<MoleEntity>(id, data, mapData, std::move(s));
    });
    RegisterEntity(PlayerEntity::str, [](EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                                         std::unique_ptr<EntityService> s) {
        return std::make_unique<PlayerEntity>(id, data, mapData, std::move(s));
    });
    RegisterEntity(ArrowEntity::str, [](EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                                        std::unique_ptr<EntityService> s) {
        return std::make_unique<ArrowEntity>(id, data, mapData, std::move(s));
    });
    RegisterEntity(CoinEntity::str, [](EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                                       std::unique_ptr<EntityService> s) {
        return std::make_unique<CoinEntity>(id, data, mapData, std::move(s));
    });
    RegisterEntity(RectEntity::str, [](EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                                       std::unique_ptr<EntityService> s) {
        return std::make_unique<RectEntity>(id, data, mapData, std::move(s));
    });
}

Factory::~Factory() = default;

std::unique_ptr<BasicEntity> Factory::Create(const PropertyData& data, const Shared::MapData& mapData,
                                             std::unique_ptr<EntityService> service) const
{
    auto it = map_.find(data.typeStr_);

    if (it != map_.end()) {
        return it->second(id_++, data, mapData, std::move(service));
    }

    LOG_ERROR("Could not create entity of %s", DUMP2("type", data.typeStr_));
    return nullptr;
}

void Factory::RegisterEntity(const std::string& typeStr, Factory::CreateFn createFn)
{
    map_[typeStr] = createFn;
}

}  // namespace Entity

}  // namespace FA
