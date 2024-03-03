/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "EffectIf.h"

#include "RectangleShape.h"

namespace FA {

namespace Shared {

class FadeEffect : public EffectIf
{
public:
    FadeEffect(const sf::Vector2f& position, const sf::Vector2f& size, float duration);

    virtual void DrawTo(Graphic::IRenderTarget& renderTarget) const override;
    virtual void Update(float deltaTime) override;

private:
    Graphic::RectangleShape fadeRect_;
    int startAlpha_ = 0;
    int endAlpha_ = 255;
    float duration_{};
    float currentTime_{};
};

}  // namespace Shared

}  // namespace FA
