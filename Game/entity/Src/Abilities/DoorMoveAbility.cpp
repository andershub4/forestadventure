/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "DoorMoveAbility.h"

#include <unordered_map>

#include "Body.h"
#include "Constant/Entity.h"
#include "Events/StartDoorMoveEvent.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<MoveDirection, sf::Vector2f> dirToVector = {{MoveDirection::None, {0.0, 0.0}},
                                                                     {MoveDirection::Up, {0.0, -1.0}},
                                                                     {MoveDirection::Right, {1.0, 0.0}},
                                                                     {MoveDirection::Down, {0.0, 1.0}},
                                                                     {MoveDirection::Left, {-1.0, 0.0}}};

}  // namespace

DoorMoveAbility::DoorMoveAbility(Body &body, std::function<void(State currentState, const sf::Vector2f &)> updateFn)
    : body_(body)
    , velocity_(Constant::stdVelocity / 2)
    , updateFn_(updateFn)
{}

DoorMoveAbility::~DoorMoveAbility() = default;

void DoorMoveAbility::Enter(std::shared_ptr<BasicEvent> event)
{
    auto m = std::dynamic_pointer_cast<StartDoorMoveEvent>(event);
    enterPosition_ = m->enterPosition_;
    exitPosition_ = m->exitPosition_;
    state_ = State::StartMovingToEntrance;
}

void DoorMoveAbility::Update(float deltaTime)
{
    distance_ += deltaTime * currentVelocity_;
    body_.position_ += movementVector_ * deltaTime;
    updateFn_(state_, exitPosition_);

    if (state_ == State::StartMovingToEntrance) {
        currentVelocity_ = velocity_;
        movementVector_ = CalculateMovementVector(MoveDirection::Up);
        state_ = State::MovingToEntrance;
    }
    else if (state_ == State::MovingToEntrance) {
        bool entranceFinished = body_.position_.y < (enterPosition_.y - moveDistance_);
        if (entranceFinished) {
            state_ = State::StartMovingFromExit;
        }
    }
    else if (state_ == State::StartMovingFromExit) {
        distance_ = 0.0f;
        movementVector_ = CalculateMovementVector(MoveDirection::Down);
        body_.position_ = exitPosition_;
        body_.position_.y -= moveDistance_;
        state_ = State::MovingFromExit;
    }
    else if (state_ == State::MovingFromExit) {
        bool exitFinished = distance_ > moveDistance_;
        if (exitFinished) {
            movementVector_ = {};
            currentVelocity_ = 0.0f;
            state_ = State::Done;
        }
    }
}

void DoorMoveAbility::Exit()
{
    distance_ = 0.0f;
    movementVector_ = {};
}

sf::Vector2f DoorMoveAbility::CalculateMovementVector(MoveDirection moveDir) const
{
    auto it = dirToVector.find(moveDir);
    if (it != dirToVector.end()) {
        return it->second * velocity_;
    }

    return {};
}

}  // namespace Entity

}  // namespace FA
