/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "AnimationTraits.h"

#include "RectangleShapeIf.h"
#include "Resource/ColliderFrame.h"

namespace FA {

namespace Shared {

template <>
struct AnimationTraits<Shared::ColliderFrame>
{
    using DrawableT = Graphic::RectangleShapeIf;
    static void Apply(const Shared::ColliderFrame& frame, Graphic::RectangleShapeIf& drawable, bool center)
    {
        drawable.setSize(frame.size_);
        if (center) {
            drawable.setOrigin(frame.center_.x, frame.center_.y);
        }
    }
};

}  // namespace Shared

}  // namespace FA
