/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StaticEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

const std::string StaticEntity::str = "Static";

StaticEntity::StaticEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                           const EntityService& service)
    : BasicEntity(id, data, mapData, service)
{}

StaticEntity::~StaticEntity() = default;

}  // namespace Entity

}  // namespace FA
