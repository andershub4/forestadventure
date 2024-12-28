/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "AnimationTraits.h"

#include "Resource/ImageFrame.h"
#include "SpriteIf.h"

namespace FA {

namespace Shared {

template <>
struct AnimationTraits<Shared::ImageFrame>
{
    using DrawableT = Graphic::SpriteIf;
    static void Apply(const Shared::ImageFrame& frame, Graphic::SpriteIf& drawable, bool center)
    {
        drawable.setTexture(*frame.texture_);
        drawable.setTextureRect(frame.rect_);
        if (center) {
            drawable.setOrigin(frame.center_.x, frame.center_.y);
        }
    }
};

}  // namespace Shared

}  // namespace FA
