/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageSprite.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

namespace Entity {

ImageSprite::ImageSprite() = default;

ImageSprite::~ImageSprite() = default;

void ImageSprite::RegisterImage(const std::string &name, const Image &image)
{
    // check for already registered name
    map_[name] = image;
}

void ImageSprite::Update(float deltaTime)
{
    if (currentImage_.IsValid()) {
        currentImage_.Update(deltaTime);
        currentImage_.ApplyTo(sprite_);
    }
}

void ImageSprite::DrawTo(sf::RenderTarget &renderTarget)
{
    if (currentImage_.IsValid()) {
        renderTarget.draw(sprite_);
    }
}

void ImageSprite::SetImage(const std::string &key)
{
    // if key is in map_
    currentImage_ = map_.at(key);
    currentImage_.ApplyTo(sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

void ImageSprite::ApplyTo(std::function<void(sf::Sprite &sprite)> applyFn)
{
    // Here setting of position, scale and rotation can be done
    if (currentImage_.IsValid()) {
        applyFn(sprite_);
    }
}

}  // namespace Entity

}  // namespace FA
