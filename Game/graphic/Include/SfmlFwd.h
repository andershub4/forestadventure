/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

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

class RectangleShape;
class Texture;
class RenderWindow;
class RenderTarget;
class RenderTexture;
class Event;
class Sprite;
class View;
class Font;
class Drawable;
class Color;
class VideoMode;
class Text;	

typedef unsigned int Uint32;

}  // namespace sf
