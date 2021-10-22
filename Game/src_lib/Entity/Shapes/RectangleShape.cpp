/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "RectangleShape.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

namespace Entity {

void RectangleShape::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(rShape_);
}

void RectangleShape::SetTransform(const sf::Vector2f &position, float scale)
{
    rShape_.setPosition(position);
    rShape_.setScale(scale, scale);
}

void RectangleShape::SetSize(const sf::Vector2f &size)
{
    rShape_.setSize(size);
}

}  // namespace Entity

}  // namespace FA
