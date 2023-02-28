/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/MoveAbility.h"
#include "Constant/Entity.h"
#include "Events/DeadEvent.h"
#include "Events/StartMoveEvent.h"
#include "PropertyConverter.h"
#include "PropertyData.h"
#include "Resource/ImageData.h"
#include "Resource/SheetId.h"
#include "Sprites/ImageSprite.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<MoveDirection, float> arrowRotation = {{MoveDirection::Down, 180.0f},
                                                                {MoveDirection::Left, 270.0f},
                                                                {MoveDirection::Right, 90.0f},
                                                                {MoveDirection::Up, 0.0f}};
}  // namespace

const std::string ArrowEntity::str = "Arrow";

PropertyData ArrowEntity::CreatePropertyData(const sf::Vector2f& position, MoveDirection dir)
{
    PropertyData data;
    std::unordered_map<std::string, std::string> properties;
    std::stringstream ss;
    ss << dir;
    properties["MoveDirection"] = ss.str();
    data.typeStr_ = ArrowEntity::str;
    data.properties_ = properties;
    data.position_ = position;

    return data;
}

ArrowEntity::ArrowEntity(EntityId id, const PropertyData& data, const EntityService& service)
    : BasicEntity(id, data, service)
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::RegisterProperties()
{
    propertyStore_.Register<MoveDirection>("MoveDirection", MoveDirection::Down);
}

void ArrowEntity::ReadProperties(const std::unordered_map<std::string, std::string>& properties)
{
    for (const auto& p : properties) {
        if (p.first == "MoveDirection") {
            MoveDirection dir = ToValue<MoveDirection>(p.second);
            propertyStore_.Set<MoveDirection>(p.first, dir);
        }
    }
}

void ArrowEntity::OnBeginIdle()
{
    auto dir = propertyStore_.Get<MoveDirection>("MoveDirection");
    auto event = std::make_shared<StartMoveEvent>(dir);
    HandleEvent(event);
}

void ArrowEntity::OnBeginMove(MoveDirection moveDirection)
{
    body_.rotation_ = arrowRotation.at(moveDirection);
}

void ArrowEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    body_.position_ += delta;
    bool outsideMap = !entityService_.IsInsideMap(body_.position_);

    if (outsideMap) {
        HandleEvent(std::make_shared<DeadEvent>());
    }
}

void ArrowEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                 const PropertyData& data)
{
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterIgnoreEvents({EventType::Collision});

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity * 8.0f, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveSprite = std::make_shared<ImageSprite<std::string>>([]() { return "Move"; });
    moveSprite->RegisterImage("Move", entityService_.MakeImage({Shared::SheetId::Arrow, {0, 0}}));
    moveState->RegisterAbility(move);
    moveState->RegisterSprite(moveSprite);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
