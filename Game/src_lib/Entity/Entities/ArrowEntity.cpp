/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/AnimationAbility.h"
#include "Entity/Abilities/MoveAbility.h"
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
    propertyManager_.GetRef<sf::Vector2f>("Position") += delta;

    auto mapW = static_cast<float>(entityService_.GetMapSize().x);
    auto mapH = static_cast<float>(entityService_.GetMapSize().y);
    auto mapRect = sf::FloatRect(0, 0, mapW, mapH);
    bool outsideMap = !mapRect.contains(propertyManager_.Get<sf::Vector2f>("Position"));

    if (outsideMap) {
        entityService_.DeleteEntity(GetId());
    }
}

void ArrowEntity::OnUpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
}

void ArrowEntity::RegisterProperties()
{
    propertyManager_.Register<float>("Rotation", 0.0);
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
}

void ArrowEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void ArrowEntity::RegisterStates(const PropertyData& data)
{
    auto getKey = [this]() { return "Move"; };
    auto updateAnimation = [this](const Animation& animation) { OnUpdateAnimation(animation); };

    auto idleState = RegisterState(StateType::Idle, true);
    idleState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    idleState->BindAction(Action::Ignore(), EventType::Collision);

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        constant::Entity::stdVelocity * 8.0f, [this](FaceDirection f) { OnBeginMove(f); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    auto a = entityService_.MakeAnimation({SheetId::Arrow, {{0, 0}, 1, 0}, false});
    moveAnimation->RegisterAnimation("Move", a);
    moveState->RegisterAbility(move);
    moveState->RegisterAbility(moveAnimation);
    moveState->BindAction(Action::ChangeTo(StateType::Idle), EventType::StopMove);
}

}  // namespace Entity

}  // namespace FA
