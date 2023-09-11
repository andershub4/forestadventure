/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprite.h"

#include <SFML/Graphics/Sprite.hpp>

#include "Texture.h"

namespace FA {

namespace Graphic {

Sprite::Sprite()
    : sprite_(std::make_shared<sf::Sprite>())
{}

Sprite::~Sprite() = default;

void Sprite::setTexture(const ITexture& texture, bool resetRect)
{
    texture_ = &texture;
    const sf::Texture& sfTexture = dynamic_cast<const Texture&>(texture);
    sprite_->setTexture(sfTexture, resetRect);
}

void Sprite::setTextureRect(const sf::IntRect& rectangle)
{
    sprite_->setTextureRect(rectangle);
}

void Sprite::setColor(const sf::Color& color)
{
    sprite_->setColor(color);
}

const ITexture* Sprite::getTexture() const
{
    return texture_;
}

sf::FloatRect Sprite::getLocalBounds() const
{
    return sprite_->getLocalBounds();
}

void Sprite::setPosition(float x, float y)
{
    sprite_->setPosition(x, y);
}

void Sprite::setPosition(const sf::Vector2f& position)
{
    sprite_->setPosition(position);
}

void Sprite::setRotation(float angle)
{
    sprite_->setRotation(angle);
}

void Sprite::setOrigin(float x, float y)
{
    sprite_->setOrigin(x, y);
}

Sprite::operator const sf::Drawable&() const
{
    return *sprite_;
}

}  // namespace Graphic

}  // namespace FA
