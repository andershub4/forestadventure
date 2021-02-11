/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Enum/MoveDirection.h"

namespace FA {

class Movement
{
public:
    Movement() = default;
    Movement(float velocity);

    void Update(float deltaTime);

    void ApplyTo(sf::RectangleShape* rectShape);
    void SetDirection(MoveDirection direction);

private:
    float velocity_{};
    sf::Vector2f movementVector_{};
    sf::Vector2f offset_{};
};

}  // namespace FA
