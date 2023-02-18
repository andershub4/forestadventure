/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Effect/NullEffect.h"

namespace FA {

namespace Shared {

NullEffect::NullEffect()
    : BasicEffect()
{}

void NullEffect::DrawTo(sf::RenderTarget& renderTarget) const
{}

void NullEffect::Update(float deltaTime)
{}

}  // namespace Shared

}  // namespace FA
