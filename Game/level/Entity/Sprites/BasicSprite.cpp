/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicSprite.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

namespace Entity {

void BasicSprite::SetPosition(const sf::Vector2f &position)
{
    sprite_.setPosition(position);
}

void BasicSprite::SetRotation(float rot)
{
    sprite_.setRotation(rot);
}

void BasicSprite::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

}  // namespace Entity

}  // namespace FA
