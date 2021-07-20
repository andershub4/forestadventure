/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TextureManager.h"

#include <SFML/Graphics/Texture.hpp>

#include "Logging.h"

namespace FA {

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

void TextureManager::Add(const std::string &name, const std::string &path)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(path)) {
        textures_.emplace(name, std::move(texture));
    }
    else {
        LOG_ERROR("Could not load ", path);
    }
}

const sf::Texture *TextureManager::Get(const std::string &name) const
{
    auto it = textures_.find(name);

    if (it != textures_.end()) return it->second.get();

    LOG_ERROR("Could not get ", name);

    return nullptr;
}

}  // namespace FA
