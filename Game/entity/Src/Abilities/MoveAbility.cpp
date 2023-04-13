/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveAbility.h"

#include <unordered_map>

#include <SFML/System/Vector2.hpp>

#include "Events/StartMoveEvent.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<MoveDirection, sf::Vector2f> dirToVector = {{MoveDirection::None, {0.0, 0.0}},
                                                                     {MoveDirection::Up, {0.0, -1.0}},
                                                                     {MoveDirection::Right, {1.0, 0.0}},
                                                                     {MoveDirection::Down, {0.0, 1.0}},
                                                                     {MoveDirection::Left, {-1.0, 0.0}}};

}  // namespace

MoveAbility::MoveAbility(float velocity, std::function<void(MoveDirection)> enterFn,
                         std::function<void(const sf::Vector2f&)> updateFn)
    : enterFn_(enterFn)
    , updateFn_(updateFn)
    , velocity_(velocity)
{}

MoveAbility::~MoveAbility() = default;

void MoveAbility::Enter(std::shared_ptr<BasicEvent> event)
{
    auto m = std::dynamic_pointer_cast<StartMoveEvent>(event);
    auto it = dirToVector.find(m->moveDirection_);
    if (it != dirToVector.end()) {
        movementVector_ = it->second * velocity_;
    }

    enterFn_(m->moveDirection_);
}

void MoveAbility::Update(float deltaTime)
{
    sf::Vector2f delta = {movementVector_.x * deltaTime, movementVector_.y * deltaTime};
    updateFn_(delta);
}

}  // namespace Entity

}  // namespace FA
