/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/AnimationAbility.h"
#include "Entity/PropertyData.h"
#include "Entity/State.h"

namespace FA {

namespace Entity {

TileEntity::TileEntity(EntityId id, Level& level, const Shared::SheetManager& sheetManager,
                       Shared::MessageBus& messageBus)
    : BasicEntity(id, level, sheetManager, messageBus)
{}

TileEntity::~TileEntity() = default;

void TileEntity::OnUpdateAnimation(const Shared::Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
}

void TileEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void TileEntity::RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    auto updateAnimation = [this](const Shared::Animation& animation) { OnUpdateAnimation(animation); };

    auto idleAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    float t = constant::Entity::stdSwitchTime;
    auto a = Shared::Animation(data.frames_, 0, t);
    idleAnimation->RegisterAnimation("Idle", a);
    idleState->RegisterAbility(idleAnimation);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
