/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include "PropertyData.h"
#include "Resource/ColliderData.h"
#include "Resource/SheetId.h"
#include "ShapeParts/AnimationPart.h"
#include "ShapeParts/ColliderPart.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

using namespace Shared::SheetId;

const std::vector<Shared::ImageData> idle{{Coin, {0, 0}}, {Coin, {1, 0}}, {Coin, {2, 0}}, {Coin, {3, 0}}};
const std::vector<Shared::ColliderData> colliderIdle{{Coin, {0, 0}}, {Coin, {1, 0}}, {Coin, {2, 0}}, {Coin, {3, 0}}};

}  // namespace

const std::string CoinEntity::str = "Coin";

CoinEntity::CoinEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                       const EntityService& service)
    : BasicEntity(id, data, mapData, service)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    auto animation = service_.MakeAnimation(idle);
    auto shapePart = AnimationPart::Create(animation);
    idleState->RegisterShapePart(shapePart);
    auto collider = service_.MakeCollider(colliderIdle);
    auto colliderPart = ColliderPart::Create(collider);
    idleState->RegisterColliderPart(colliderPart);
}

}  // namespace Entity

}  // namespace FA
