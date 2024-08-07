/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "RectangleShapeIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RectangleShape : public RectangleShapeIf
{
public:
    RectangleShape();
    RectangleShape(const sf::Vector2f &size);

    virtual sf::FloatRect getLocalBounds() const override;
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void setSize(const sf::Vector2f &size) override;
    virtual void setPosition(const sf::Vector2f &position) override;
    virtual void setPosition(float x, float y) override;
    virtual void setRotation(float angle) override;
    virtual void setFillColor(const sf::Color &color) override;
    virtual void setOutlineColor(const sf::Color &color) override;
    virtual void setOutlineThickness(float thickness) override;
    virtual void setOrigin(float x, float y) override;

private:
    std::shared_ptr<sf::RectangleShape> rectangleShape_;

private:
    virtual operator const sf::Drawable &() const override;
};

}  // namespace Graphic

}  // namespace FA
