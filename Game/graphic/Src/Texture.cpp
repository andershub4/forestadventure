/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Texture.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace FA {

namespace Graphic {

Texture::Texture()
    : internalTexture_(std::make_shared<sf::Texture>())
    , texture_(internalTexture_.get())
{}

Texture::Texture(const sf::Texture& texture)
    : texture_(const_cast<sf::Texture*>(&texture))
{}

Texture::~Texture() = default;

bool Texture::create(unsigned int width, unsigned int height)
{
    return texture_->create(width, height);
}

bool Texture::loadFromFile(const std::string& filename)
{
    return texture_->loadFromFile(filename, sf::IntRect());
}

bool Texture::loadFromFile(const std::string& filename, const sf::IntRect& area)
{
    return texture_->loadFromFile(filename, area);
}

bool Texture::loadFromMemory(const void* data, std::size_t size)
{
    return texture_->loadFromMemory(data, size, sf::IntRect());
}

bool Texture::loadFromMemory(const void* data, std::size_t size, const sf::IntRect& area)
{
    return texture_->loadFromMemory(data, size, area);
}

sf::Vector2u Texture::getSize() const
{
    return texture_->getSize();
}

}  // namespace Graphic

}  // namespace FA
