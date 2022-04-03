/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Image.h"

#include <SFML/Graphics/Sprite.hpp>

namespace FA {

Image::Image(const Frame& frame)
    : frame_(frame)
    , isValid_(true)
{}

void Image::ApplyTo(sf::Sprite& sprite)
{
    sprite.setTexture(*frame_.texture_);
    sprite.setTextureRect(frame_.rect_);
}

void Image::Update(float deltaTime)
{}

bool Image::IsValid() const
{
    return isValid_;
}

}  // namespace FA
