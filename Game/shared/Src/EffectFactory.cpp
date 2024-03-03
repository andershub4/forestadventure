/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EffectFactory.h"

#include "Effect/FadeEffect.h"
#include "Effect/NullEffect.h"

namespace FA {

namespace Shared {

std::unique_ptr<EffectIf> EffectFactory::CreateFadeEffect(std::shared_ptr<Graphic::IRectangleShape> rect,
                                                          const sf::Vector2f& position, float duration) const
{
    return std::make_unique<FadeEffect>(rect, position, duration);
}

std::unique_ptr<EffectIf> EffectFactory::CreateNullEffect() const
{
    return std::make_unique<NullEffect>();
}

}  // namespace Shared

}  // namespace FA
