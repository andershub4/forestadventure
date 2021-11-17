/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveMode.h"

#include <unordered_map>

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/EntityService.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Shapes/Shape.h"
#include "Enum/MoveDirection.h"

namespace {

const std::unordered_map<FA::MoveDirection, sf::Vector2f> dirToVector = {{FA::MoveDirection::None, {0.0, 0.0}},
                                                                         {FA::MoveDirection::Up, {0.0, -1.0}},
                                                                         {FA::MoveDirection::Right, {1.0, 0.0}},
                                                                         {FA::MoveDirection::Down, {0.0, 1.0}},
                                                                         {FA::MoveDirection::Left, {-1.0, 0.0}}};

}  // namespace

namespace FA {

namespace Entity {

MoveMode::MoveMode(EntityService *owner)
    : BasicMode(owner)
{}

void MoveMode::Enter(std::shared_ptr<BasicEvent> event)
{
    auto m = std::dynamic_pointer_cast<StartMoveEvent>(event);
    SetDirection(m->moveDirection_, m->faceDirection_);
    Owner()->GetShape()->Set(FrameType::Move);
}

void MoveMode::Exit()
{
    auto faceDir = Owner()->GetAttribute<FaceDirectionAttribute>()->GetDirection();
    SetDirection(MoveDirection::None, faceDir);
}

void MoveMode::Awake()
{
    transform_ = Owner()->GetAttribute<TransformAttribute>();
    velocity_ = Owner()->GetAttribute<VelocityAttribute>();
    faceDirection_ = Owner()->GetAttribute<FaceDirectionAttribute>();
}

void MoveMode::Update(float deltaTime)
{
    Owner()->GetShape()->Update(deltaTime);

    sf::Vector2f offset = {movementVector_.x * deltaTime, movementVector_.y * deltaTime};
    transform_->Move(offset);
}

void MoveMode::SetDirection(MoveDirection direction, FaceDirection faceDir)
{
    auto it = dirToVector.find(direction);
    if (it != dirToVector.end()) {
        movementVector_ = it->second * velocity_->GetVelocity();
    }
    faceDirection_->SetDirection(faceDir);
}

}  // namespace Entity

}  // namespace FA
