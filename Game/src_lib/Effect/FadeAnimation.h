/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class FadeAnimation
{
public:
    FadeAnimation(const sf::Vector2f& size, float seconds);

    void DrawTo(sf::RenderTarget& renderTarget) const;
    void Update(float deltaTime);
    bool IsFinished() const;

private:
    sf::Clock clock_;
    sf::RectangleShape fadeRect_;
    int startAlpha_ = 0;
    int endAlpha_ = 255;
    sf::Time targetTime_;
    sf::Time currentTime_;
};

}  // namespace FA
