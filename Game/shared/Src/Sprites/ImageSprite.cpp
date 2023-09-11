/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprites/ImageSprite.h"

#include "ISprite.h"

namespace FA {

namespace Shared {

ImageSprite::ImageSprite(std::shared_ptr<Graphic::ISprite> sprite, const Frame& frame)
    : BasicSprite(sprite)
    , frame_(frame)
{}

void ImageSprite::Update(float deltaTime)
{
    sprite_->setTexture(*frame_.texture_);
    sprite_->setTextureRect(frame_.rect_);
}

}  // namespace Shared

}  // namespace FA
