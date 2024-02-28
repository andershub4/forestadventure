/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "View.h"

#include <SFML/Graphics/View.hpp>

namespace FA {

namespace Graphic {

View::View()
    : view_(std::make_shared<sf::View>())
{}

View::~View() = default;

void View::setSize(const sf::Vector2f& size)
{
    view_->setSize(size);
}

void View::zoom(float factor)
{
    view_->zoom(factor);
}

void View::setCenter(const sf::Vector2f& center)
{
    view_->setCenter(center);
}

}  // namespace Graphic

}  // namespace FA
