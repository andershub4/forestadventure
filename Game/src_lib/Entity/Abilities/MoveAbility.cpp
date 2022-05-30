/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveAbility.h"

#include <unordered_map>

#include <SFML/System/Vector2.hpp>

#include "Entity/Events/StartMoveEvent.h"

namespace {

const std::unordered_map<FA::MoveDirection, sf::Vector2f> dirToVector = {{FA::MoveDirection::None, {0.0, 0.0}},
                                                                         {FA::MoveDirection::Up, {0.0, -1.0}},
                                                                         {FA::MoveDirection::Right, {1.0, 0.0}},
                                                                         {FA::MoveDirection::Down, {0.0, 1.0}},
                                                                         {FA::MoveDirection::Left, {-1.0, 0.0}}};

}  // namespace

namespace FA {

namespace Entity {

MoveAbility::MoveAbility(float velocity, std::function<void(FaceDirection)> enterFn,
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

    enterFn_(m->faceDirection_);
}

void MoveAbility::Update(float deltaTime)
{
    sf::Vector2f delta = {movementVector_.x * deltaTime, movementVector_.y * deltaTime};
    updateFn_(delta);
}

}  // namespace Entity

}  // namespace FA
