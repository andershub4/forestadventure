/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

namespace FA {

enum class MoveDirection;

namespace Entity {

class TransformComponent;

class MovementComponent
{
public:
    MovementComponent() = default;
    MovementComponent(float velocity);

    void Update(float deltaTime);

    void ApplyTo(TransformComponent &transform) const;
    void SetDirection(MoveDirection direction);

private:
    float velocity_{};
    sf::Vector2f movementVector_{};
    sf::Vector2f offset_{};
};

}  // namespace Entity

}  // namespace FA
