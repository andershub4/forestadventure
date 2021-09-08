/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "BasicComponent.h"

namespace FA {

enum class MoveDirection;

namespace Entity {

class BasicState;
class TransformComponent;

class MovementComponent : public BasicComponent
{
public:
    MovementComponent(TransformComponent &transform, float velocity);

    virtual void Update(float deltaTime) override;

    void SetDirection(MoveDirection direction);
    void Execute(BasicState &oldState);

private:
    float velocity_{};
    sf::Vector2f movementVector_{};
    TransformComponent &transform_;
};

}  // namespace Entity

}  // namespace FA
