/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/View.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class Camera
{
public:
    Camera(const sf::Vector2f& position, const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize);
    ~Camera();

    void UpdatePosition(sf::RenderTarget& renderTarget);

private:
    sf::Vector2u mapSize_{};
    sf::View view_;
    sf::Vector2f centerPos_;
    const sf::Vector2f& position_;
    sf::Vector2f minViewPosition_{};
    sf::Vector2f maxViewPosition_{};

private:
    sf::Vector2f CalcViewPosition(const sf::Vector2f& position) const;
    float Clamp(float value, float lower, float upper) const;
};

}  // namespace FA
