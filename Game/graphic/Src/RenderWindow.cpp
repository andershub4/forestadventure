/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "RenderWindow.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Sprite.h"

namespace FA {

namespace Graphic {

RenderWindow::RenderWindow()
    : renderWindow_(std::make_unique<sf::RenderWindow>())
{}

RenderWindow::~RenderWindow() = default;

void RenderWindow::draw(const IDrawable& drawable)
{
    const sf::Drawable& sfDrawable = drawable;
    return renderWindow_->draw(sfDrawable);
}

void RenderWindow::display()
{
    renderWindow_->display();
}

bool RenderWindow::pollEvent(sf::Event& event)
{
    return renderWindow_->pollEvent(event);
}

void RenderWindow::create(sf::VideoMode mode, const std::string& title)
{
    renderWindow_->create(mode, title);
}

void RenderWindow::create(sf::VideoMode mode, const std::string& title, sf::Uint32 style)
{
    renderWindow_->create(mode, title, style);
}

void RenderWindow::close()
{
    renderWindow_->close();
}

void RenderWindow::setFramerateLimit(unsigned int limit)
{
    renderWindow_->setFramerateLimit(limit);
}

void RenderWindow::clear()
{
    renderWindow_->clear(sf::Color(0, 0, 0, 255));
}

void RenderWindow::clear(const sf::Color& color)
{
    renderWindow_->clear(color);
}

void RenderWindow::setView(const sf::View& view)
{
    renderWindow_->setView(view);
}

}  // namespace Graphic

}  // namespace FA
