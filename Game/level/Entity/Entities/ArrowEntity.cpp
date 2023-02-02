/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/MoveAbility.h"
#include "Entity/PropertyData.h"
#include "Entity/Sprites/ImageSprite.h"
#include "Entity/State.h"
#include "Level/Level.h"
#include "Resource/ImageData.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<MoveDirection, float> arrowRotation = {{MoveDirection::Down, 180.0f},
                                                                {MoveDirection::Left, 270.0f},
                                                                {MoveDirection::Right, 90.0f},
                                                                {MoveDirection::Up, 0.0f}};
}  // namespace

ArrowEntity::ArrowEntity(EntityId id, Level& level, const EntityService& service)
    : BasicEntity(id, level, service)
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::OnBeginMove(MoveDirection moveDirection)
{
    body_.rotation_ = arrowRotation.at(moveDirection);
}

void ArrowEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    body_.position_ += delta;
    bool outsideMap = !entityService_.IsInsideMap(body_.position_);

    if (outsideMap) {
        level_.DeleteEntity(GetId());
    }
}

void ArrowEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                 const PropertyData& data)
{
    auto getKey = [this]() { return "Move"; };

    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterIgnoreEvents({EventType::Collision});

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity * 8.0f, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto i = entityService_.MakeImage({Shared::SheetId::Arrow, {0, 0}});
    std::unordered_map<std::string, Shared::Image> images{{"Move", i}};
    auto moveImage = std::make_shared<ImageSprite>(getKey, images);
    moveState->RegisterAbility(move);
    moveState->RegisterSprite(moveImage);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
