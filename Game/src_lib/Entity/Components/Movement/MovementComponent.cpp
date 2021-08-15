/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MovementComponent.h"

#include <unordered_map>

#include "Entity/Components/Transform/TransformComponent.h"
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

MovementComponent::MovementComponent(TransformComponent &transform, float velocity)
    : velocity_(velocity)
    , transform_(transform)
{}

void MovementComponent::Update(float deltaTime)
{
    offset_ = {movementVector_.x * deltaTime, movementVector_.y * deltaTime};
    transform_.Move(offset_);
}

void MovementComponent::SetDirection(MoveDirection direction)
{
    auto it = dirToVector.find(direction);
    if (it != dirToVector.end()) {
        movementVector_ = it->second * velocity_;
    }
}

}  // namespace Entity

}  // namespace FA