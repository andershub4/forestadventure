/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class TextureManager;
enum class TileType;

class TileSet
{
public:
    struct Tile
    {
        const sf::Texture* texture_ = nullptr;
        sf::IntRect rect_;
    };

    TileSet(TextureManager& textureManager);
    ~TileSet();

    void Load();
    Tile GetTile(TileType type) const;

private:
    TextureManager& textureManager_;
    const sf::Texture* texture_;
};

}  // namespace FA
