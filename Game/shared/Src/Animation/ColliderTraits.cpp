/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Animation/ColliderTraits.h"

#include "RectangleShapeIf.h"
#include "Resource/ColliderFrame.h"

namespace FA {

namespace Shared {

void AnimationTraits<ColliderFrame>::Apply(const ColliderFrame& frame, Graphic::RectangleShapeIf& drawable, bool center)
{
    drawable.setSize(frame.size_);
    if (center) {
        drawable.setOrigin(frame.center_.x, frame.center_.y);
    }
}

}  // namespace Shared

}  // namespace FA
