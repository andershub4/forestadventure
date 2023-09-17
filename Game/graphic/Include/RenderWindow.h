/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "IRenderWindow.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RenderWindow : public IRenderWindow
{
public:
    RenderWindow();
    virtual ~RenderWindow();

    virtual void draw(const IDrawable &drawable) override;
    virtual void display() override;
    virtual bool pollEvent(sf::Event &event) override;
    virtual void create(sf::VideoMode mode, const std::string &title) override;
    virtual void create(sf::VideoMode mode, const std::string &title, sf::Uint32 style) override;
    virtual void close() override;
    virtual void setFramerateLimit(unsigned int limit) override;
    virtual void clear() override;
    virtual void clear(const sf::Color &color) override;
    virtual void setView(const sf::View &view) override;

private:
    std::unique_ptr<sf::RenderWindow> renderWindow_;
};

}  // namespace Graphic

}  // namespace FA
