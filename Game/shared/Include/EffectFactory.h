/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class IRectangleShape;

}  // namespace Graphic

namespace Shared {

class EffectIf;

class EffectFactory
{
public:
    std::unique_ptr<EffectIf> CreateFadeEffect(std::shared_ptr<Graphic::IRectangleShape> rect,
                                               const sf::Vector2f& position, float duration) const;
    std::unique_ptr<EffectIf> CreateNullEffect() const;
};

}  // namespace Shared

}  // namespace FA
