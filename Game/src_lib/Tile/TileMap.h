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

class TileSet;
enum class TileType;

namespace Tile {

class TileMap
{
public:
    TileMap(const TileSet &tileSet);
    ~TileMap();
    void Load();
    void DrawTo(sf::RenderTarget &renderTarget);
    sf::Vector2u GetSize() const;

private:
    static const unsigned int nTilesXPerScreen{40};
    static const unsigned int nTilesYPerScreen{24};
    static const unsigned int nScreensX{2};
    static const unsigned int nScreensY{2};
    static const unsigned int scale{2};
    static const unsigned int tileSize{16};
    static const unsigned int nCols{nTilesXPerScreen * nScreensX};
    static const unsigned int nRows{nTilesYPerScreen * nScreensY};

    sf::Sprite tileMap_;
    sf::RenderTexture renderTexture_;
    const TileSet &tileSet_;

private:
    TileType RandomizeType() const;
};

}  // namespace Tile

}  // namespace FA
