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
#include "Entity/State.h"
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
                         EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus, mapSize)
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::OnBeginMove(FaceDirection faceDirection)
{
    rotation_ = arrowRotation.at(faceDirection);
}

void ArrowEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    position_ += delta;

    // auto mapW = static_cast<float>(entityService_.GetMapSize().x);
    // auto mapH = static_cast<float>(entityService_.GetMapSize().y);
    // auto mapRect = sf::FloatRect(0, 0, mapW, mapH);
    auto mapRect = sf::FloatRect({0.0f, 0.0f}, entityService_.GetMapSize());
    bool outsideMap = !mapRect.contains(position_);

    if (outsideMap) {
        entityService_.DeleteEntity(GetId());
    }
}

void ArrowEntity::OnUpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
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
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeState(StateType::Move, event); });
    idleState->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {});

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        constant::Entity::stdVelocity * 8.0f, [this](FaceDirection f) { OnBeginMove(f); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    auto a = entityService_.MakeAnimation({SheetId::Arrow, {{0, 0}, 1, 0}, false});
    moveAnimation->RegisterAnimation("Move", a);
    moveState->RegisterAbility(move);
    moveState->RegisterAbility(moveAnimation);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeState(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
