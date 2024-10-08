/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <memory>

#include "Animation/ImageAnimation.h"
#include "PropertyData.h"
#include "Resource/ImageData.h"
#include "ShapeParts/SingleAnimationPart.h"
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
    auto animation = service_.CreateImageAnimation(data.graphic_.animation_);
    auto part = std::make_shared<SingleAnimationPart<Shared::ImageAnimation>>(animation);
    idleState->RegisterShapePart(part);
}

}  // namespace Entity

}  // namespace FA
