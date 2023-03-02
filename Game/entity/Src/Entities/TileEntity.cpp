/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "PropertyData.h"
#include "Sprites/AnimationSprite.h"
#include "State.h"

namespace FA {

namespace Entity {

const std::string TileEntity::str = "Tile";

TileEntity::TileEntity(EntityId id, const PropertyData& data, const EntityService& service)
    : BasicEntity(id, data, service)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    float t = Constant::stdSwitchTime;
    auto a = Shared::Animation(data.graphic_.animation_, 0, t);
    auto sprite = std::make_shared<AnimationSprite<std::string>>([]() { return "Idle"; }, false);
    sprite->RegisterResource("Idle", a);
    idleState->RegisterSprite(sprite);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
