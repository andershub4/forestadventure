/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

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

class ITexture;

class ISprite : public IDrawable
{
public:
    virtual ~ISprite() = default;
    virtual void setTexture(const ITexture &texture, bool resetRect = false) = 0;
    virtual void setTextureRect(const sf::IntRect &rectangle) = 0;
    virtual void setColor(const sf::Color &color) = 0;
    virtual const ITexture *getTexture() const = 0;

    virtual sf::FloatRect getLocalBounds() const = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    virtual void setRotation(float angle) = 0;

    virtual void setOrigin(float x, float y) = 0;
};

}  // namespace Graphic

}  // namespace FA
