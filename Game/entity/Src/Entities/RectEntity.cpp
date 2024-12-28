/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "RectEntity.h"

#include "Animation/Animation.h"
#include "RectangleShape.h"
#include "Resource/ColliderData.h"
#include "ShapeParts/SingleAnimationPart.h"
#include "State.h"

namespace FA {

namespace Entity {

const std::string RectEntity::str = "Rect";

RectEntity::RectEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service)
    : BasicEntity(id, data, std::move(service))
{}

RectEntity::~RectEntity() = default;

void RectEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const Shared::EntityData& data)
{
    const sf::Vector2i rectSize = static_cast<sf::Vector2i>(data.size_);
    const Shared::ColliderData colliderData(rectSize);
    const std::vector<Shared::ColliderData> idleColliders{colliderData};
    auto colliderAnimation = service_->CreateColliderAnimation(idleColliders);
    auto rect = idleState->RegisterCollider();
    auto colliderPart = std::make_shared<SingleAnimationPart<Shared::ColliderFrame>>(colliderAnimation, *rect);
    idleState->RegisterColliderPart(colliderPart);
}

}  // namespace Entity

}  // namespace FA
