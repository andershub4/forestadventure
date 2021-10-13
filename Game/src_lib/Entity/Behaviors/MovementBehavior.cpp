/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MovementBehavior.h"

#include <unordered_map>

#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/States/MoveState.h"
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

MovementBehavior::MovementBehavior(PropertyHandler *owner)
    : BasicBehavior(owner)
{}

void MovementBehavior::Awake()
{
    transform_ = Owner()->GetAttribute<TransformAttribute>();
    velocity_ = Owner()->GetAttribute<VelocityAttribute>();
}

void MovementBehavior::Update(float deltaTime)
{
    sf::Vector2f offset = {movementVector_.x * deltaTime, movementVector_.y * deltaTime};
    transform_->Move(offset);
}

void MovementBehavior::SetDirection(MoveDirection direction)
{
    auto it = dirToVector.find(direction);
    if (it != dirToVector.end()) {
        movementVector_ = it->second * velocity_->GetVelocity();
    }
}

void MovementBehavior::Execute(BasicState &oldState)
{
    oldState.SwitchState<MoveState>();
}

}  // namespace Entity

}  // namespace FA
