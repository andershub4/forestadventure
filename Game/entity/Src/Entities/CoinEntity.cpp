/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include <memory>

#include "Animation/ColliderAnimation.h"
#include "Animation/ImageAnimation.h"
#include "Events/CollisionEvent.h"
#include "Events/DeadEvent.h"
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

const sf::IntRect rect{1, 1, 4, 5};

const std::vector<Shared::ImageData> idleImages{coin1, coin2, coin3, coin4};
const std::vector<Shared::ColliderData> idleColliders{{coin1, rect}, {coin2, rect}, {coin3, rect}, {coin4, rect}};

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
    idleState->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {
        auto collisionEvent = std::dynamic_pointer_cast<CollisionEvent>(event);
        if (service_.GetType(collisionEvent->id_) == EntityType::Player) {
            HandleEvent(std::make_shared<DeadEvent>());
        }
    });
}

}  // namespace Entity

}  // namespace FA
