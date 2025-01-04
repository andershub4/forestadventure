/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Animation/ImageTraits.h"

#include "Resource/ImageFrame.h"
#include "SpriteIf.h"

namespace FA {

namespace Shared {

void AnimationTraits<ImageFrame>::Apply(const Shared::ImageFrame& frame, Graphic::SpriteIf& drawable, bool center)
{
    drawable.setTexture(*frame.texture_);
    drawable.setTextureRect(frame.rect_);
    if (center) {
        drawable.setOrigin(frame.center_.x, frame.center_.y);
    }
}

}  // namespace Shared

}  // namespace FA
