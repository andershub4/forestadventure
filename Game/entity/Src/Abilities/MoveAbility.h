/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include <functional>

#include "AbilityIf.h"

#include "Enum/MoveDirection.h"

namespace FA {

namespace Entity {

class MoveAbility : public AbilityIf
{
public:
    MoveAbility(float velocity, std::function<void(MoveDirection)> enterFn,
                std::function<void(const sf::Vector2f&)> updateFn);
    virtual ~MoveAbility();

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;
    virtual void Update(float deltaTime) override;

private:
    sf::Vector2f movementVector_{};
    std::function<void(MoveDirection)> enterFn_;
    std::function<void(const sf::Vector2f&)> updateFn_;
    float velocity_{};
};

}  // namespace Entity

}  // namespace FA
