/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class EffectIf;

class EffectFactory
{
public:
    std::unique_ptr<EffectIf> CreateFadeEffect(const sf::Vector2f& position, const sf::Vector2f& size,
                                               float duration) const;
    std::unique_ptr<EffectIf> CreateNullEffect() const;
};

}  // namespace Shared

}  // namespace FA
