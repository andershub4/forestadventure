/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>

#include "AbilityIf.h"

#include <SFML/System/Vector2.hpp>

#include "Enum/MoveDirection.h"

namespace FA {

namespace Entity {

struct Body;

class DoorMoveAbility : public AbilityIf
{
public:
    enum class State {
        Uninitialized,
        StartMovingToEntrance,
        MovingToEntrance,
        StartMovingFromExit,
        MovingFromExit,
        Done
    };

    DoorMoveAbility(Body &body, float velocity, std::function<void(State currentState, const sf::Vector2f &)> updateFn);
    virtual ~DoorMoveAbility();

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;
    virtual void Update(float deltaTime) override;
    virtual void Exit() override;

private:
    float velocity_{};
    float currentVelocity_{};
    float distance_{};
    Body &body_;
    sf::Vector2f enterPosition_{};
    sf::Vector2f exitPosition_{};
    sf::Vector2f movementVector_{};
    State state_{State::Uninitialized};
    std::function<void(State currentState, const sf::Vector2f &)> updateFn_;

private:
    sf::Vector2f CalculateMovementVector(MoveDirection moveDir) const;
};

}  // namespace Entity

}  // namespace FA
