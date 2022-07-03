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
#include "Entity/State.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

CoinEntity::CoinEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus, mapSize)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::OnUpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void CoinEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void CoinEntity::RegisterStates(const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    auto updateAnimation = [this](const Animation& animation) { OnUpdateAnimation(animation); };

    auto idleState = RegisterState(StateType::Idle, true);
    auto idleAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    auto a = entityService_.MakeAnimation({SheetId::Coin, {{0, 0}, 4, 0}, false});
    idleAnimation->RegisterAnimation("Idle", a);
    idleState->RegisterAbility(idleAnimation);
    idleState->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {});
}

}  // namespace Entity

}  // namespace FA
