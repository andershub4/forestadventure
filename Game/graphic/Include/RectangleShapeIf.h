/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SfmlFwd.h"
#include "ShapeIf.h"

namespace FA {

namespace Graphic {

class RectangleShapeIf : public ShapeIf
{
public:
    virtual ~RectangleShapeIf() = default;

    virtual void setSize(const sf::Vector2f &size) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    virtual void setFillColor(const sf::Color &color) = 0;
};

}  // namespace Graphic

}  // namespace FA
