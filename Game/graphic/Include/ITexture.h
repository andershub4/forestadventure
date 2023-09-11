/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

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

}  // namespace sf

namespace FA {

namespace Graphic {

class ITexture
{
public:
    virtual ~ITexture() = default;
    virtual bool create(unsigned int width, unsigned int height) = 0;
    virtual bool loadFromFile(const std::string &filename) = 0;
    virtual bool loadFromFile(const std::string &filename, const sf::IntRect &area) = 0;
    virtual bool loadFromMemory(const void *data, std::size_t size) = 0;
    virtual bool loadFromMemory(const void *data, std::size_t size, const sf::IntRect &area) = 0;

    virtual sf::Vector2u getSize() const = 0;
};

}  // namespace Graphic

}  // namespace FA
