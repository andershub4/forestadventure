/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "ITexture.h"

#include <SFML/Graphics/Texture.hpp>

namespace FA {

namespace Graphic {

class Texture : public ITexture
{
public:
    virtual bool create(unsigned int width, unsigned int height) override;
    virtual bool loadFromFile(const std::string &filename, const sf::IntRect &area = sf::IntRect()) override;
    virtual bool loadFromMemory(const void *data, std::size_t size, const sf::IntRect &area = sf::IntRect()) override;
    // etc

private:
    sf::Texture texture_;
};

}  // namespace Graphic

}  // namespace FA
