/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Image.h"

#include <SFML/Graphics/Sprite.hpp>

namespace FA {

Image::Image(const sf::Texture* texture, const sf::IntRect& frame, float rotation)
    : texture_(texture)
    , frame_(frame)
    , rotation_(rotation)
    , isValid_(true)
{}

void Image::ApplyTo(sf::Sprite& sprite)
{
    sprite.setTexture(*texture_);
    sprite.setTextureRect(frame_);
    sprite.setRotation(rotation_);
}

void Image::Update(float deltaTime)
{}

bool Image::IsValid() const
{
    return isValid_;
}

}  // namespace FA
