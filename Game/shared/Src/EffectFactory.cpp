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

std::unique_ptr<EffectIf> EffectFactory::CreateFadeEffect(const sf::Vector2f& position, const sf::Vector2f& size,
                                                          float duration) const
{
    return std::make_unique<FadeEffect>(position, size, duration);
}

std::unique_ptr<EffectIf> EffectFactory::CreateNullEffect() const
{
    return std::make_unique<NullEffect>();
}

}  // namespace Shared

}  // namespace FA
