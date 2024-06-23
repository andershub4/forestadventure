/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include "PropertyData.h"
#include "Resource/ImageData.h"
#include "ShapeParts/AnimationPart.h"
#include "State.h"

namespace FA {

namespace Entity {

const std::string TileEntity::str = "Tile";

TileEntity::TileEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                       const EntityService& service)
    : BasicEntity(id, data, mapData, service)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    auto animation = service_.MakeAnimation(data.graphic_.animation_);
    auto part = AnimationPart::Create(animation, false);
    idleState->RegisterShapePart(part);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
