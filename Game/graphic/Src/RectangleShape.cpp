/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "RectangleShape.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace FA {

namespace Graphic {

RectangleShape::RectangleShape()
    : rectangleShape_(std::make_shared<sf::RectangleShape>(sf::Vector2f(0, 0)))
{}

RectangleShape::RectangleShape(const sf::Vector2f& size)
    : rectangleShape_(std::make_shared<sf::RectangleShape>(size))
{}

void RectangleShape::setSize(const sf::Vector2f& size)
{
    rectangleShape_->setSize(size);
}

void RectangleShape::setPosition(const sf::Vector2f& position)
{
    rectangleShape_->setPosition(position);
}

void RectangleShape::setPosition(float x, float y)
{
    rectangleShape_->setPosition(x, y);
}

void RectangleShape::setFillColor(const sf::Color& color)
{
    rectangleShape_->setFillColor(color);
}

void RectangleShape::setOutlineColor(const sf::Color& color)
{
    rectangleShape_->setOutlineColor(color);
}

void RectangleShape::setOutlineThickness(float thickness)
{
    rectangleShape_->setOutlineThickness(thickness);
}

RectangleShape::operator const sf::Drawable&() const
{
    return *rectangleShape_;
}

}  // namespace Graphic

}  // namespace FA
