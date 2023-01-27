/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/ImageAbility.h"
#include "Entity/Abilities/MoveAbility.h"
#include "Entity/PropertyData.h"
#include "Entity/State.h"
#include "Level/Level.h"
#include "Resource/ImageData.h"
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
    body_.rotation_ = arrowRotation.at(faceDirection);
}

void ArrowEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    body_.position_ += delta;

    auto mapRect = level_.GetMapRect();
    bool outsideMap = !mapRect.contains(body_.position_);

    if (outsideMap) {
        level_.DeleteEntity(GetId());
    }
}

void ArrowEntity::RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data)
{
    auto getKey = [this]() { return "Move"; };

    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterIgnoreEvents({EventType::Collision});

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        constant::Entity::stdVelocity * 8.0f, [this](FaceDirection f) { OnBeginMove(f); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveImage = std::make_shared<ImageAbility>(getKey);
    auto i = entityService_.MakeImage({Shared::SheetId::Arrow, {0, 0}});
    moveImage->RegisterImage("Move", i);
    moveState->RegisterAbility(move);
    moveState->RegisterImage(moveImage);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
