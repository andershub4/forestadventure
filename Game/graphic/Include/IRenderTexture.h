/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "IRenderTarget.h"

namespace sf {

template <class T>
class Vector2;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;

class View;
class Color;

}  // namespace sf

namespace FA {

namespace Graphic {

class ITexture;

class IRenderTexture : public IRenderTarget
{
public:
    virtual ~IRenderTexture() override = default;
    virtual bool create(unsigned int width, unsigned int height, bool depthBuffer) = 0;
    virtual void display() = 0;
    virtual sf::Vector2u getSize() const = 0;
    virtual const Graphic::ITexture& getTexture() const = 0;
    virtual void clear() = 0;
    virtual void clear(const sf::Color& color) = 0;
    virtual void setView(const sf::View& view) = 0;
    virtual sf::Vector2f mapPixelToCoords(const sf::Vector2i& point) const = 0;
};

}  // namespace Graphic

}  // namespace FA
