/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FadeTransition.h"

#include "EffectIf.h"

namespace FA {

namespace Scene {

FadeTransition::FadeTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(1.0f, nextSceneFn)
{}

FadeTransition::~FadeTransition() = default;

std::unique_ptr<Shared::EffectIf> FadeTransition::CreateEffect(std::shared_ptr<Graphic::IRectangleShape> rect,
                                                               const sf::Vector2f& position) const
{
    return factory_.CreateFadeEffect(rect, position, duration_);
}

}  // namespace Scene

}  // namespace FA
