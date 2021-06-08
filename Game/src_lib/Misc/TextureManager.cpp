/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TextureManager.h"

#include <SFML/Graphics/Texture.hpp>

#include "Logger.h"

namespace FA {

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

const sf::Texture* TextureManager::GetTexture(const std::string& file)
{
    auto it = textures_.find(file);

    if (it != textures_.end()) return it->second.get();  // if it exist, return texture

    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(file)) {
        textures_.emplace(file, std::move(texture));
        return textures_.at(file).get();
    }
    else {
        LOG_ERROR("Could not load ", file);
        return nullptr;
    }
}

}  // namespace FA
