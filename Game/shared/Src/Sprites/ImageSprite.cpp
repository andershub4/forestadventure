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

ImageSprite::ImageSprite(std::shared_ptr<Graphic::SpriteIf> sprite, const Frame& frame)
    : BasicCoolSprite<ImageSpriteIf>(sprite)
{
    bool isValid = frame.texture_ != nullptr && frame.rect_.width != 0 && frame.rect_.height != 0;

    if (isValid) {
        sprite_->setTexture(*frame.texture_);
        sprite_->setTextureRect(frame.rect_);
    }
    else {
        LOG_WARN("%s is invalid", DUMP(frame));
    }
}

}  // namespace Shared

}  // namespace FA
