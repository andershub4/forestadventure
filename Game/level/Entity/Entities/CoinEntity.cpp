/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include "Entity/Abilities/AnimationAbility.h"
#include "Entity/PropertyData.h"
#include "Entity/State.h"
#include "Resource/AnimationData.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

CoinEntity::CoinEntity(EntityId id, Level& level, const Shared::SheetManager& sheetManager,
                       Shared::MessageBus& messageBus)
    : BasicEntity(id, level, sheetManager, messageBus)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    auto idleAnimation = std::make_shared<AnimationAbility>(getKey);
    auto a = entityService_.MakeAnimation({Shared::SheetId::Coin, {{0, 0}, 4, 0}, false});
    idleAnimation->RegisterAnimation("Idle", a);
    idleState->RegisterAnimation(idleAnimation);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
