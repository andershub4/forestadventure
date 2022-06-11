/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/MoveAbility.h"
#include "Entity/ImageSprite.h"
#include "Entity/PropertyData.h"
#include "Entity/States/BasicState.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, float> arrowRotation = {{FaceDirection::Down, 180.0f},
                                                                {FaceDirection::Left, 270.0f},
                                                                {FaceDirection::Right, 90.0f},
                                                                {FaceDirection::Up, 0.0f}};
}  // namespace

ArrowEntity::ArrowEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::OnBeginMove(FaceDirection faceDirection)
{
    auto rotation = arrowRotation.at(faceDirection);
    propertyManager_.Set("Rotation", rotation);
}

void ArrowEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    auto current = propertyManager_.Get<sf::Vector2f>("Position");
    auto position = current + delta;
    propertyManager_.Set("Position", position);

    auto mapW = static_cast<float>(entityService_.GetMapSize().x);
    auto mapH = static_cast<float>(entityService_.GetMapSize().y);
    auto mapRect = sf::FloatRect(0, 0, mapW, mapH);
    bool outsideMap = !mapRect.contains(position);

    if (outsideMap) {
        entityService_.DeleteEntity(GetId());
    }
}

void ArrowEntity::RegisterAbilities()
{
    auto move = std::make_shared<MoveAbility>(
        constant::Entity::stdVelocity * 8.0f, [this](FaceDirection f) { OnBeginMove(f); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });

    RegisterAbility(MoveAbility::Type(), move);
}

void ArrowEntity::RegisterStates()
{
    auto idleState = RegisterState(StateType::Idle, true);
    idleState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    idleState->BindAction(Action::Ignore(), EventType::Collision);

    auto moveState = RegisterState(StateType::Move);
    moveState->AddShape("Main", nullptr);
    moveState->AddAbility(MoveAbility::Type());
    moveState->BindAction(Action::ChangeTo(StateType::Idle), EventType::StopMove);
}

void ArrowEntity::RegisterProperties()
{
    propertyManager_.Register<float>("Rotation", 0.0);
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
}

void ArrowEntity::OnBeginShape(Shape& shape, StateType stateType)
{
    auto sprite = shape.GetImageSprite("Main");

    std::stringstream ss;
    ss << stateType;
    sprite->SetImage(ss.str());

    sprite->ApplyTo([this](sf::Sprite& sprite) { sprite.setRotation(propertyManager_.Get<float>("Rotation")); });
}

void ArrowEntity::OnUpdateShape(Shape& shape)
{
    shape.SetPosition(propertyManager_.Get<sf::Vector2f>("Position"));
}

void ArrowEntity::RegisterShapes(const PropertyData& data)
{
    auto shape = std::make_shared<Shape>([this](StateType stateType, Shape& shape) { OnBeginShape(shape, stateType); },
                                         [this](Shape& shape) { OnUpdateShape(shape); });

    auto sprite = std::make_shared<ImageSprite>();

    auto i = entityService_.MakeImage({SheetId::Arrow, {0, 0}});
    sprite->RegisterImage("Move", i);

    shape->RegisterImageSprite("Main", sprite);

    RegisterShape("Main", shape);
}

}  // namespace Entity

}  // namespace FA
