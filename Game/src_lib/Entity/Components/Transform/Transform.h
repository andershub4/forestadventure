/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

namespace FA {

namespace Entity {

class Transform
{
public:
    Transform() = default;
    Transform(const sf::Vector2f &position, float scale);

    void Move(const sf::Vector2f &offset);
    sf::Vector2f GetPosition() const { return position_; }
    float GetScale() const { return scale_; }

private:
    sf::Vector2f position_{};
    float scale_{};
};

}  // namespace Entity

}  // namespace FA
