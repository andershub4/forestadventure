/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntranceEntity.h"

#include "Animation/ColliderAnimation.h"
#include "PropertyConverter.h"
#include "Resource/ColliderData.h"
#include "ShapeParts/SingleAnimationPart.h"
#include "State.h"

namespace FA {

namespace Entity {

const std::string EntranceEntity::str = "Entrance";

EntranceEntity::EntranceEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service)
    : BasicEntity(id, data, std::move(service))
{}

EntranceEntity::~EntranceEntity() = default;

void EntranceEntity::RegisterProperties()
{
    propertyStore_.Register("ExitId", 0);
}

void EntranceEntity::ReadProperties(const std::unordered_map<std::string, std::string>& properties)
{
    for (const auto& p : properties) {
        if (p.first == "ExitId") {
            int entranceId = ToValue<int>(p.second);
            propertyStore_.Set(p.first, entranceId);
        }
    }
}

void EntranceEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                    const Shared::EntityData& data)
{
    // const sf::Vector2i rectSize = static_cast<sf::Vector2i>(data.size_);
    const sf::Vector2i rectSize = static_cast<sf::Vector2i>(sf::Vector2f(1.0f, 1.0f));
    const Shared::ColliderData colliderData(rectSize);
    const std::vector<Shared::ColliderData> idleColliders{colliderData};
    auto colliderAnimation = service_->CreateColliderAnimation(idleColliders);
    auto colliderPart = std::make_shared<SingleAnimationPart<Shared::ColliderAnimation>>(colliderAnimation);
    idleState->RegisterMainColliderPart(colliderPart);
}

}  // namespace Entity

}  // namespace FA
