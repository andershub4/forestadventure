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
#include "Resource/ColliderData.h"
#include "Resource/ImageData.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "ShapeParts/SingleAnimationPart.h"
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

CoinEntity::CoinEntity(EntityId id, const PropertyData& data, std::unique_ptr<EntityService> service)
    : BasicEntity(id, data, std::move(service))
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    auto imageAnimation = service_->CreateImageAnimation(idleImages);
    imageAnimation->Center();
    auto shapePart = std::make_shared<SingleAnimationPart<Shared::ImageAnimation>>(imageAnimation);
    idleState->RegisterShapePart(shapePart);
    auto colliderAnimation = service_->CreateColliderAnimation(idleColliders);
    colliderAnimation->Center();
    auto colliderPart = std::make_shared<SingleAnimationPart<Shared::ColliderAnimation>>(colliderAnimation);
    idleState->RegisterColliderPart(colliderPart);
    idleState->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {
        auto collisionEvent = std::dynamic_pointer_cast<CollisionEvent>(event);
        if (service_->GetEntity(collisionEvent->id_).Type() == EntityType::Player) {
            HandleEvent(std::make_shared<DeadEvent>());
        }
    });
}

}  // namespace Entity

}  // namespace FA
