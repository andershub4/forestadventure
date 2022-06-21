/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/AnimationAbility.h"
#include "Entity/PropertyData.h"
#include "Entity/States/BasicState.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

CoinEntity::CoinEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterProperties()
{
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
    propertyManager_.Register<float>("Rotation", 0.0);
}

void CoinEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void CoinEntity::UpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
}

void CoinEntity::RegisterStates(const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    auto updateAnimation = [this](const Animation& animation) { UpdateAnimation(animation); };

    auto idleState = RegisterState(StateType::Idle, true);
    auto idleAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    auto a = entityService_.MakeAnimation({SheetId::Coin, {{0, 0}, 4, 0}, false});
    idleAnimation->RegisterAnimation("Idle", a);
    idleState->RegisterAbility(idleAnimation);
    idleState->BindAction(Action::Ignore(), EventType::Collision);
}

}  // namespace Entity

}  // namespace FA
