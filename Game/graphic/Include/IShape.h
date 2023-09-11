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

class IShape : public IDrawable
{
public:
    virtual ~IShape() = default;
};

}  // namespace Graphic

}  // namespace FA
