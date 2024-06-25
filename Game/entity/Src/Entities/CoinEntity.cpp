/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include "PropertyData.h"
#include "Resource/ColliderData.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "ShapeParts/AnimationPart.h"
#include "ShapeParts/ColliderPart.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

using namespace Shared::SheetId;

const Shared::SheetItem coin1{Coin, {0, 0}};
const Shared::SheetItem coin2{Coin, {1, 0}};
const Shared::SheetItem coin3{Coin, {2, 0}};
const Shared::SheetItem coin4{Coin, {3, 0}};

const std::vector<Shared::ImageData> idleImages{coin1, coin2, coin3, coin4};
const std::vector<Shared::ColliderData> idleColliders{coin1, coin2, coin3, coin4};

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
    auto imageAnimation = service_.MakeAnimation(idleImages);
    auto shapePart = AnimationPart::Create(imageAnimation);
    idleState->RegisterShapePart(shapePart);
    auto colliderAnimation = service_.MakeAnimation(idleColliders);
    auto colliderPart = ColliderPart::Create(colliderAnimation);
    idleState->RegisterColliderPart(colliderPart);
}

}  // namespace Entity

}  // namespace FA
