/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "AnimationTraits.h"

namespace FA {

namespace Graphic {

class SpriteIf;

}  // namespace Graphic

namespace Shared {

struct ImageFrame;

template <>
struct AnimationTraits<ImageFrame>
{
    using DrawableT = Graphic::SpriteIf;
    static void Apply(const ImageFrame& frame, Graphic::SpriteIf& drawable, bool center);
};

}  // namespace Shared

}  // namespace FA
