/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "AnimationTraits.h"

namespace FA {

namespace Graphic {

class RectangleShapeIf;

}  // namespace Graphic

namespace Shared {

struct ColliderFrame;

template <>
struct AnimationTraits<ColliderFrame>
{
    using DrawableT = Graphic::RectangleShapeIf;
    static void Apply(const ColliderFrame& frame, Graphic::RectangleShapeIf& drawable, bool center);
};

}  // namespace Shared

}  // namespace FA
