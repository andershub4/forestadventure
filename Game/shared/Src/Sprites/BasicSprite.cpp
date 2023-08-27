/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprites/BasicSprite.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace FA {

namespace Shared {

BasicSprite::BasicSprite(std::shared_ptr<sf::Sprite> sprite)
    : sprite_(sprite)
    , isValid_(true)
{}

void BasicSprite::SetPosition(const sf::Vector2f& position)
{
    sprite_->setPosition(position);
}

void BasicSprite::SetRotation(float rot)
{
    sprite_->setRotation(rot);
}

void BasicSprite::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*sprite_);
}

void BasicSprite::Center()
{
    sprite_->setOrigin(sprite_->getLocalBounds().width / 2, sprite_->getLocalBounds().height / 2);
}

bool BasicSprite::IsValid() const
{
    return isValid_;
}

}  // namespace Shared

}  // namespace FA
