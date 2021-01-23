/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Movement.h"

#include <unordered_map>

namespace {

const std::unordered_map<FA::MoveDirection, sf::Vector2f> dirToVector = {{FA::MoveDirection::Up, {0.0, -1.0}},
                                                                         {FA::MoveDirection::Right, {1.0, 0.0}},
                                                                         {FA::MoveDirection::Down, {0.0, 1.0}},
                                                                         {FA::MoveDirection::Left, {-1.0, 0.0}}};

}  // namespace

namespace FA {

Movement::Movement(sf::RectangleShape *rectShape, float velocity)
    : rectShape_(rectShape)
    , velocity_(velocity)
{}

void Movement::Update(float deltaTime)
{
    rectShape_->move(movementVector_.x * deltaTime, movementVector_.y * deltaTime);
}

void Movement::SetDirection(MoveDirection direction)
{
    auto it = dirToVector.find(direction);
    if (it != dirToVector.end()) {
        movementVector_ = it->second * velocity_;
    }
}

void Movement::Stop()
{
    movementVector_ = {};
}

}  // namespace FA
