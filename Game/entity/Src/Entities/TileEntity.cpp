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

TileEntity::TileEntity(EntityId id, const EntityService& service)
    : BasicEntity(id, service)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    float t = Constant::stdSwitchTime;
    auto a = Shared::Animation(data.graphic_.animation_, 0, t);
    std::unordered_map<std::string, Shared::Animation> animations{{"Idle", a}};
    auto idleAnimation = std::make_shared<AnimationSprite>(getKey, animations, false);
    idleState->RegisterSprite(idleAnimation);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
