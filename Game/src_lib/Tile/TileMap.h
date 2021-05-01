/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Tile {

struct TileMapData;

class TileMap
{
public:
    TileMap(const TileMapData &tileMapData);
    ~TileMap();
    void Load();
    void DrawTo(sf::RenderTarget &renderTarget);
    sf::Vector2u GetSize() const;

private:
    struct TileInfo
    {
        const sf::Texture *texture_ = nullptr;
        sf::IntRect uvRect_;
    };

    static const unsigned int scale{2};

    sf::Sprite tileMap_;
    sf::RenderTexture mapTexture_;
    const TileMapData &tileMapData_;

private:
    TileInfo GetTileInfo(int id);
    void ApplyTile(const TileInfo &tileInfo, const sf::Vector2i &position, sf::RenderTexture &mapTexture);
};

}  // namespace Tile

}  // namespace FA
