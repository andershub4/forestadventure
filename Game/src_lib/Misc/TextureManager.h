/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#pragma once

#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>

namespace FA {

class TextureManager
{
public:
	const sf::Texture& GetTexture(const std::string& file);

private:
	std::unordered_map<std::string, sf::Texture> textures_;
};

} // namespace FA