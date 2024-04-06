/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprites/ImageSprite.h"

#include "Logging.h"
#include "SpriteIf.h"

namespace FA {

namespace Shared {

ImageSprite::ImageSprite(const Frame& frame)
    : BasicCoolSprite<ImageSpriteIf>()
    , frame_(frame)
{
    isValid_ = frame.texture_ != nullptr && frame.rect_.width != 0 && frame.rect_.height != 0;

    if (!isValid_) {
        LOG_WARN("%s is invalid", DUMP(frame));
    }
}

void ImageSprite::ApplyTo(Graphic::SpriteIf& sprite) const
{
    if (isValid_) {
        sprite.setTexture(*frame_.texture_);
        sprite.setTextureRect(frame_.rect_);
    }
}

}  // namespace Shared

}  // namespace FA
