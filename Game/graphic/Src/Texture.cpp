/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Texture.h"

namespace FA {

namespace Graphic {

bool Texture::create(unsigned int width, unsigned int height)
{
    return texture_.create(width, height);
}

bool Texture::loadFromFile(const std::string& filename, const sf::IntRect& area)
{
    return loadFromFile(filename, area);
}

bool Texture::loadFromMemory(const void* data, std::size_t size, const sf::IntRect& area)
{
    return loadFromMemory(data, size, area);
}

}  // namespace Graphic

}  // namespace FA
