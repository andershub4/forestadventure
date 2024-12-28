/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <memory>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/MoveAbility.h"
#include "Animation/ImageAnimation.h"
#include "Constant/Entity.h"
#include "Events/CollisionEvent.h"
#include "Events/DeadEvent.h"
#include "Events/StartMoveEvent.h"
#include "PropertyConverter.h"
#include "RectangleShape.h"
#include "Resource/ColliderData.h"
#include "Resource/EntityData.h"
#include "Resource/ImageData.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "ShapeParts/SingleAnimationPart.h"
#include "Sprite.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

using namespace Shared::SheetId;

const Shared::SheetItem arrow{Arrow, {0, 0}};

const std::vector<Shared::ImageData> images{arrow};
const std::vector<Shared::ColliderData> colliders{arrow};

const std::unordered_map<MoveDirection, float> arrowRotation = {{MoveDirection::Down, 180.0f},
                                                                {MoveDirection::Left, 270.0f},
                                                                {MoveDirection::Right, 90.0f},
                                                                {MoveDirection::Up, 0.0f}};

MoveDirection FaceDirToMoveDir(FaceDirection faceDir)
{
    MoveDirection moveDir = MoveDirection::None;

    if (faceDir == FaceDirection::Down)
        moveDir = MoveDirection::Down;
    else if (faceDir == FaceDirection::Up)
        moveDir = MoveDirection::Up;
    else if (faceDir == FaceDirection::Left)
        moveDir = MoveDirection::Left;
    else if (faceDir == FaceDirection::Right)
        moveDir = MoveDirection::Right;

    return moveDir;
}

}  // namespace

const std::string ArrowEntity::str = "Arrow";

Shared::EntityData ArrowEntity::CreateEntityData(const sf::Vector2f& position, FaceDirection dir)
{
    Shared::EntityData data;
    std::unordered_map<std::string, std::string> properties;
    std::stringstream ss;
    ss << dir;
    properties["FaceDirection"] = ss.str();
    data.typeStr_ = ArrowEntity::str;
    data.properties_ = properties;
    data.position_ = position;

    return data;
}

ArrowEntity::ArrowEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service)
    : BasicEntity(id, data, std::move(service))
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::RegisterProperties()
{
    propertyStore_.Register("FaceDirection", FaceDirection::Undefined);
}

void ArrowEntity::ReadProperties(const std::unordered_map<std::string, std::string>& properties)
{
    for (const auto& p : properties) {
        if (p.first == "FaceDirection") {
            FaceDirection dir = ToValue<FaceDirection>(p.second);
            propertyStore_.Set(p.first, dir);
        }
    }
}

void ArrowEntity::OnBeginIdle()
{
    FaceDirection faceDir;
    propertyStore_.Get("FaceDirection", faceDir);
    auto dir = FaceDirToMoveDir(faceDir);
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
}

void ArrowEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                 const Shared::EntityData& data)
{
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });

    auto moveState = RegisterState(StateType::Move);
    auto imageAnimation = service_->CreateImageAnimation(images);
    imageAnimation->Center();
    auto sprite = moveState->RegisterSprite();
    auto shapePart = std::make_shared<SingleAnimationPart<Shared::ImageFrame>>(imageAnimation, *sprite);
    moveState->RegisterShapePart(shapePart);
    auto colliderAnimation = service_->CreateColliderAnimation(colliders);
    colliderAnimation->Center();
    auto rect = moveState->RegisterCollider();
    auto colliderPart = std::make_shared<SingleAnimationPart<Shared::ColliderFrame>>(colliderAnimation, *rect);
    moveState->RegisterColliderPart(colliderPart);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity * 8.0f, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    moveState->RegisterAbility(move);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    moveState->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {
        auto collisionEvent = std::dynamic_pointer_cast<CollisionEvent>(event);
        if (service_->GetEntity(collisionEvent->id_).Type() == EntityType::Mole) {
            HandleEvent(std::make_shared<DeadEvent>());
        }
    });
    moveState->RegisterEventCB(EventType::OutsideTileMap, [this](std::shared_ptr<BasicEvent> event) {
        HandleEvent(std::make_shared<DeadEvent>());
    });
}

}  // namespace Entity

}  // namespace FA
