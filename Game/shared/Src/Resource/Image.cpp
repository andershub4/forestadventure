/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Resource/Image.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace FA {

namespace Shared {

Image::Image(std::shared_ptr<sf::Sprite> sprite, const Frame& frame)
    : sprite_(sprite)
    , frame_(frame)
    , isValid_(true)
{}

void Image::Update(float deltaTime)
{
    sprite_->setTexture(*frame_.texture_);
    sprite_->setTextureRect(frame_.rect_);
    sprite_->setOrigin(sprite_->getLocalBounds().width / 2, sprite_->getLocalBounds().height / 2);
}

void Image::SetPosition(const sf::Vector2f& position)
{
    sprite_->setPosition(position);
}

void Image::SetRotation(float rot)
{
    sprite_->setRotation(rot);
}

void Image::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*sprite_);
}

void Image::Center()
{
    sprite_->setOrigin(sprite_->getLocalBounds().width / 2, sprite_->getLocalBounds().height / 2);
}

bool Image::IsValid() const
{
    return isValid_;
}

}  // namespace Shared

}  // namespace FA
