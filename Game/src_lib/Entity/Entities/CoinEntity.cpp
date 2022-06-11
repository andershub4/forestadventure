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
    idleState->AddShape("Main", nullptr);
    idleState->BindAction(Action::Ignore(), EventType::Collision);
}

void CoinEntity::RegisterProperties()
{
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
}

void CoinEntity::OnBeginShape(Shape& shape, StateType stateType)
{
    auto sprite = shape.GetAnimationSprite("Main");

    std::stringstream ss;
    ss << stateType;
    sprite->SetAnimation(ss.str());
}

void CoinEntity::OnUpdateShape(Shape& shape)
{
    shape.SetPosition(propertyManager_.Get<sf::Vector2f>("Position"));
}

void CoinEntity::RegisterShapes(const PropertyData& data)
{
    auto shape = std::make_shared<Shape>([this](StateType stateType, Shape& shape) { OnBeginShape(shape, stateType); },
                                         [this](Shape& shape) { OnUpdateShape(shape); });

    auto sprite = std::make_shared<AnimationSprite>();

    auto a = entityService_.MakeAnimation({SheetId::Coin, {{0, 0}, 4, 0}, false});
    sprite->RegisterAnimation("Idle", a);

    shape->RegisterAnimationSprite("Main", sprite);

    RegisterShape("Main", shape);
}

}  // namespace Entity

}  // namespace FA
