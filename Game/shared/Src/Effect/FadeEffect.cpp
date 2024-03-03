/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Effect/FadeEffect.h"

#include <SFML/Graphics/Color.hpp>

#include "RenderWindow.h"

namespace FA {

namespace Shared {

FadeEffect::FadeEffect(const sf::Vector2f& position, const sf::Vector2f& size, float duration)
    : EffectIf()
    , fadeRect_(size)
    , duration_(duration)
{
    fadeRect_.setPosition(position);
    fadeRect_.setFillColor(sf::Color(0, 0, 0, 0));
}

void FadeEffect::DrawTo(Graphic::IRenderTarget& renderTarget) const
{
    renderTarget.draw(fadeRect_);
}

void FadeEffect::Update(float deltaTime)
{
    currentTime_ += deltaTime;
    float currentAlpha = startAlpha_ + (endAlpha_ - startAlpha_) * (currentTime_ / duration_);

    fadeRect_.setFillColor(sf::Color(0, 0, 0, static_cast<unsigned int>(currentAlpha)));
}

}  // namespace Shared

}  // namespace FA
