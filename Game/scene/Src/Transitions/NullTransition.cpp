/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "NullTransition.h"

#include "EffectIf.h"

namespace FA {

namespace Scene {

NullTransition::NullTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(0.0, nextSceneFn)
{}

NullTransition::~NullTransition() = default;

std::unique_ptr<Shared::EffectIf> NullTransition::CreateEffect(const sf::Vector2f& position,
                                                               const sf::Vector2f& size) const
{
    return factory_.CreateNullEffect();
}

}  // namespace Scene

}  // namespace FA
