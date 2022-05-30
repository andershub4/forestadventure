/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include <functional>

#include "BasicAbility.h"

#include "Enum/FaceDirection.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class MoveAbility : public BasicAbility
{
public:
    MoveAbility(float velocity, std::function<void(FaceDirection)> enterFn,
                std::function<void(const sf::Vector2f&)> updateFn);
    virtual ~MoveAbility();

    static const std::string Type() { return "MoveAbility"; }

    virtual void Enter(std::shared_ptr<BasicEvent> event);
    virtual void Update(float deltaTime);

private:
    sf::Vector2f movementVector_{};
    std::function<void(FaceDirection)> enterFn_;
    std::function<void(const sf::Vector2f&)> updateFn_;
    float velocity_{};
};

}  // namespace Entity

}  // namespace FA
