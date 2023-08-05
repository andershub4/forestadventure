/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/Graphics/Rect.hpp>

namespace FA {

namespace Graphic {

class ITexture
{
public:
    virtual bool create(unsigned int width, unsigned int height) = 0;
    virtual bool loadFromFile(const std::string &filename, const sf::IntRect &area = sf::IntRect()) = 0;
    virtual bool loadFromMemory(const void *data, std::size_t size, const sf::IntRect &area = sf::IntRect()) = 0;
    // etc
};

}  // namespace Graphic

}  // namespace FA
