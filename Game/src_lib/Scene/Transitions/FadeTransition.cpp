/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FadeTransition.h"

#include "Constant/Screen.h"

namespace FA {

namespace Scene {

FadeTransition::FadeTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(1.0f, nextSceneFn)
{}

FadeTransition::~FadeTransition() = default;

std::unique_ptr<BasicEffect> FadeTransition::CreateEffect(const sf::Vector2f& position, const sf::Vector2f& size) const
{
    return std::make_unique<FadeEffect>(position, size, seconds_);
}

}  // namespace Scene

}  // namespace FA
