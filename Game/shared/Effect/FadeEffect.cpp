/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FadeEffect.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

namespace Shared {

FadeEffect::FadeEffect(const sf::Vector2f& position, const sf::Vector2f& size, float seconds)
    : BasicEffect()
    , fadeRect_(size)
    , targetTime_(sf::seconds(seconds))
{
    fadeRect_.setPosition(position);
    fadeRect_.setFillColor(sf::Color(0, 0, 0, 0));
}

void FadeEffect::DrawTo(sf::RenderTarget& renderTarget) const
{
    renderTarget.draw(fadeRect_);
}

void FadeEffect::Update(float deltaTime)
{
    currentTime_ = clock_.getElapsedTime();
    float currentAlpha = startAlpha_ + (endAlpha_ - startAlpha_) * (currentTime_ / targetTime_);
    fadeRect_.setFillColor(sf::Color(0, 0, 0, static_cast<unsigned int>(currentAlpha)));
}

}  // namespace Shared

}  // namespace FA
