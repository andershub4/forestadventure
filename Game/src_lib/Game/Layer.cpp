/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Layer.h"

#include "Constant/Screen.h"

namespace FA {

Layer::Layer()
{
    renderTexture_.create(constant::Screen::width, constant::Screen::height);
    sprite_.setTexture(renderTexture_.getTexture());
}

void Layer::Draw(const sf::Drawable& drawable)
{
    renderTexture_.draw(drawable);
}

void Layer::Display()
{
    renderTexture_.display();
}

void Layer::Clear()
{
    renderTexture_.clear(sf::Color::Transparent);
}

void Layer::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(sprite_);
}

}  // namespace FA
