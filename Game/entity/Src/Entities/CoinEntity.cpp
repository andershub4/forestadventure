/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include <memory>

#include "Animation/ColliderAnimation.h"
#include "Animation/ImageAnimation.h"
#include "PropertyData.h"
#include "RectangleShape.h"
#include "Resource/ColliderData.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "Selections/SingleSelection.h"
#include "ShapeParts/AnimationPart.h"
#include "Sprite.h"
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
    auto imageAnimation = std::make_shared<Shared::ImageAnimation>(std::make_shared<Graphic::Sprite>(),
                                                                   service_.CreateSequence(idleImages));
    imageAnimation->Center();
    auto shapePart = std::make_shared<AnimationPart<Shared::ImageAnimation>>(
        std::make_shared<SingleSelection<Shared::ImageAnimation>>(imageAnimation));
    idleState->RegisterShapePart(shapePart);
    auto colliderAnimation = std::make_shared<Shared::ColliderAnimation>(std::make_shared<Graphic::RectangleShape>(),
                                                                         service_.CreateSequence(idleColliders));
    colliderAnimation->Center();
    auto colliderPart = std::make_shared<AnimationPart<Shared::ColliderAnimation>>(
        std::make_shared<SingleSelection<Shared::ColliderAnimation>>(colliderAnimation));
    idleState->RegisterColliderPart(colliderPart);
}

}  // namespace Entity

}  // namespace FA
