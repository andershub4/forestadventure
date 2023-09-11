/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "IShape.h"

namespace sf {

template <class T>
class Vector2;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;

class Color;

}  // namespace sf

namespace FA {

namespace Graphic {

class IRectangleShape : public IShape
{
public:
    virtual ~IRectangleShape() = default;

    virtual void setSize(const sf::Vector2f &size) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    virtual void setFillColor(const sf::Color &color) = 0;
};

}  // namespace Graphic

}  // namespace FA
