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
#include "Level/Level.h"
#include "Resource/AnimationData.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, float> arrowRotation = {{FaceDirection::Down, 180.0f},
                                                                {FaceDirection::Left, 270.0f},
                                                                {FaceDirection::Right, 90.0f},
                                                                {FaceDirection::Up, 0.0f}};
}  // namespace

ArrowEntity::ArrowEntity(EntityId id, Level& level, const Shared::SheetManager& sheetManager,
                         Shared::MessageBus& messageBus)
    : BasicEntity(id, level, sheetManager, messageBus)
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::OnBeginMove(FaceDirection faceDirection)
{
    rotation_ = arrowRotation.at(faceDirection);
}

void ArrowEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    position_ += delta;

    auto mapRect = level_.GetMapRect();
    bool outsideMap = !mapRect.contains(position_);

    if (outsideMap) {
        level_.DeleteEntity(GetId());
    }
}

void ArrowEntity::OnUpdateAnimation(const Shared::Animation& animation)
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

void ArrowEntity::RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data)
{
    auto getKey = [this]() { return "Move"; };
    auto updateAnimation = [this](const Shared::Animation& animation) { OnUpdateAnimation(animation); };

    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterIgnoreEvents({EventType::Collision});

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        constant::Entity::stdVelocity * 8.0f, [this](FaceDirection f) { OnBeginMove(f); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    auto a = entityService_.MakeAnimation({Shared::SheetId::Arrow, {{0, 0}, 1, 0}, false});
    moveAnimation->RegisterAnimation("Move", a);
    moveState->RegisterAbility(move);
    moveState->RegisterAbility(moveAnimation);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
