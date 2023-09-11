/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "IDrawable.h"

namespace sf {

template <class T>
class Rect;
typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

template <class T>
class Vector2;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;

class Color;

}  // namespace sf

namespace FA {

namespace Graphic {

class IFont;

class IText : public IDrawable
{
public:
    virtual ~IText() = default;
    virtual void setString(const std::string &string) = 0;
    virtual void setFont(const Graphic::IFont &font) = 0;
    virtual void setCharacterSize(unsigned int size) = 0;
    virtual void setFillColor(const sf::Color &color) = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
};

}  // namespace Graphic

}  // namespace FA
