/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FadeAnimation.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

FadeAnimation::FadeAnimation(const sf::Vector2f& size, float seconds)
    : Effect(size)
    , fadeRect_(size)
    , targetTime_(sf::seconds(seconds))
{
    fadeRect_.setFillColor(sf::Color(0, 0, 0, 0));
}

void FadeAnimation::DrawTo(sf::RenderTarget& renderTarget) const
{
    renderTarget.draw(fadeRect_);
}

void FadeAnimation::Update(float deltaTime)
{
    currentTime_ = clock_.getElapsedTime();
    float currentAlpha = startAlpha_ + (endAlpha_ - startAlpha_) * (currentTime_ / targetTime_);
    fadeRect_.setFillColor(sf::Color(0, 0, 0, static_cast<unsigned int>(currentAlpha)));
}

bool FadeAnimation::IsFinished() const
{
    return currentTime_ >= targetTime_;
}

}  // namespace FA
