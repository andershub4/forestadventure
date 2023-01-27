/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Sprites/AnimationSprite.h"
#include "Entity/PropertyData.h"
#include "Entity/State.h"

namespace FA {

namespace Entity {

TileEntity::TileEntity(EntityId id, Level& level, const Shared::SheetManager& sheetManager,
                       Shared::MessageBus& messageBus)
    : BasicEntity(id, level, sheetManager, messageBus)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    float t = constant::Entity::stdSwitchTime;
    auto a = Shared::Animation(data.graphic_.animation_, 0, t);
    std::unordered_map<std::string, Shared::Animation> animations{{"Idle", a}};
    auto idleAnimation = std::make_shared<AnimationSprite>(getKey, animations, false);
    idleState->RegisterSprite(idleAnimation);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
