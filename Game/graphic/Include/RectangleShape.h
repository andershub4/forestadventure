/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "IRectangleShape.h"

namespace sf {

class RectangleShape;

}  // namespace sf

namespace FA {

namespace Graphic {

class RectangleShape : public IRectangleShape
{
public:
    RectangleShape(const sf::Vector2f &size = sf::Vector2f(0, 0));
    virtual ~RectangleShape();

    virtual void setSize(const sf::Vector2f &size) override;
    virtual void setPosition(const sf::Vector2f &position) override;
    virtual void setPosition(float x, float y) override;
    virtual void setFillColor(const sf::Color &color) override;

private:
    std::shared_ptr<sf::RectangleShape> rectangleShape_;

private:
    virtual operator const sf::Drawable &() const override;
};

}  // namespace Graphic

}  // namespace FA
