/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "TextureManager.h"

namespace FA {

const sf::Texture& TextureManager::GetTexture(const std::string& file)
{
	auto it = textures_.find(file);

	if (it != textures_.end())
		return it->second; // if it exist, return it

	// else, load and save it for later
	sf::Texture& texture = textures_[file]; // implicit creation

	texture.loadFromFile(file);

	return texture;
}

} // namespace FA