/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/AnimationSprite.h"
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

void CoinEntity::RegisterStates()
{
    auto idleState = RegisterState(StateType::Idle, true);
    idleState->AddAnimation("Main", nullptr);
    idleState->BindAction(Action::Ignore(), EventType::Collision);
}

void CoinEntity::RegisterProperties()
{
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
}

void CoinEntity::OnBeginAnimation(StateType stateType, AnimationSprite& sprite)
{
    std::stringstream ss;
    ss << stateType;
    sprite.SetAnimation(ss.str());
}

void CoinEntity::OnUpdateAnimation(AnimationSprite& sprite)
{
    sprite.ApplyTo([this](sf::Sprite& animationSprite) {
        animationSprite.setPosition(propertyManager_.Get<sf::Vector2f>("Position"));
    });
}

void CoinEntity::RegisterShape(const PropertyData& data)
{
    auto sprite = std::make_shared<AnimationSprite>(
        [this](StateType stateType, AnimationSprite& sprite) { OnBeginAnimation(stateType, sprite); },
        [this](AnimationSprite& sprite) { OnUpdateAnimation(sprite); });

    auto a = entityService_.MakeAnimation({SheetId::Coin, {{0, 0}, 4, 0}, false});
    sprite->RegisterAnimation("Idle", a);

    RegisterAnimationSprite("Main", sprite);
}

}  // namespace Entity

}  // namespace FA
