/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "ResourceManager.h"

#include <SFML/Graphics/Texture.hpp>

namespace FA {

namespace Shared {

using TextureManager = ResourceManager<std::string, sf::Texture>;

}  // namespace Shared

}  // namespace FA