/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/View.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Shared {

class Camera
{
public:
    Camera(const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize);
    ~Camera();

    void Track(const sf::Vector2f& trackingPoint);
    void UpdatePosition(float deltaTime);
    sf::View GetView() const;

private:
    sf::View view_;
    const sf::Vector2f* trackingPoint_{nullptr};
    sf::Vector2f minViewPosition_{};
    sf::Vector2f maxViewPosition_{};

private:
    sf::Vector2f CalcViewPosition() const;
    float Clamp(float value, float lower, float upper) const;
};

}  // namespace Shared

}  // namespace FA
