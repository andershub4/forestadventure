/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include "PropertyData.h"
#include "Resource/AnimationData.h"
#include "Resource/SheetId.h"
#include "Sprites/AnimationSprite.h"
#include "State.h"

namespace FA {

namespace Entity {

const std::string CoinEntity::str = "Coin";

CoinEntity::CoinEntity(EntityId id, const EntityService& service)
    : BasicEntity(id, service)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    auto a = entityService_.MakeAnimation({Shared::SheetId::Coin, {{0, 0}, 4, 0}, false});
    std::unordered_map<std::string, Shared::Animation> animations{{"Idle", a}};
    auto idleAnimation = std::make_shared<AnimationSprite>(getKey, animations);
    idleState->RegisterSprite(idleAnimation);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
