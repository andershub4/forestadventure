/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprites/ImageSprite.h"

#include "SpriteIf.h"

namespace FA {

namespace Shared {

ImageSprite::ImageSprite(std::shared_ptr<Graphic::SpriteIf> sprite, const Frame& frame)
    : BasicCoolSprite<ImageSpriteIf>(sprite)
    , frame_(frame)
{
    isValid_ = frame.texture_ != nullptr && frame.rect_.width != 0 && frame.rect_.height != 0;
}

void ImageSprite::Update(float deltaTime)
{
    if (isValid_) {
        sprite_->setTexture(*frame_.texture_);
        sprite_->setTextureRect(frame_.rect_);
    }
}

}  // namespace Shared

}  // namespace FA
