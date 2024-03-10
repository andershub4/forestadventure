/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FadeTransition.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "RectangleShape.h"
#include "IRenderTarget.h"
#include "IRenderTexture.h"

namespace FA {

namespace Scene {

FadeTransition::FadeTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(1.0f, nextSceneFn)
{}

FadeTransition::~FadeTransition() = default;

void FadeTransition::Enter(const Graphic::IRenderTexture& renderTexture)
{
    sf::Vector2f position = renderTexture.mapPixelToCoords({0, 0});
    sf::Vector2f size = static_cast<sf::Vector2f>(renderTexture.getSize());
    fadeRect_ = std::make_shared<Graphic::RectangleShape>(size);
    fadeRect_->setPosition(position);
    fadeRect_->setFillColor(sf::Color(0, 0, 0, 0));
}

void FadeTransition::DrawTo(Graphic::IRenderTarget& renderTarget) const
{
    if (fadeRect_) renderTarget.draw(*fadeRect_);
}

void FadeTransition::Update(float deltaTime)
{
    if (fadeRect_) {
        elapsedTime_ += deltaTime;
        float currentAlpha = startAlpha_ + (endAlpha_ - startAlpha_) * (elapsedTime_ / duration_);
        fadeRect_->setFillColor(sf::Color(0, 0, 0, static_cast<unsigned int>(currentAlpha)));
    }
}

}  // namespace Scene

}  // namespace FA
