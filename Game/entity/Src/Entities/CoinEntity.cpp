/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include "AnimationTable.h"
#include "PropertyData.h"
#include "Resource/AnimationData.h"
#include "Resource/SheetId.h"
#include "Sprites/AnimationSprite.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

const Shared::AnimationData idle{Shared::SheetId::Coin, {{0, 0}, 4, 0}, false};

}  // namespace

const std::string CoinEntity::str = "Coin";

CoinEntity::CoinEntity(EntityId id, const PropertyData& data, const EntityService& service)
    : BasicEntity(id, data, service)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    AnimationTable table([]() { return "Idle"; });
    table.RegisterAnimation("Idle", entityService_.MakeAnimation(idle));
    auto idleSprite = std::make_shared<AnimationSprite>(table);
    idleState->RegisterSprite(idleSprite);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
