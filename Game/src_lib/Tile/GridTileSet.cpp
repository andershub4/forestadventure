/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GridTileSet.h"

namespace FA {

namespace Tile {

GridTileSet::GridTileSet(const TileMapData::TileSet &tileSet, TextureManager &textureManager)
    : BasicTileSet(textureManager)
    , tileSet_(tileSet)
{}

GridTileSet::~GridTileSet() = default;

void GridTileSet::Load()
{
    auto p = tileSet_.image_.textureFilePath_;
    auto w = tileSet_.image_.width_;
    auto h = tileSet_.image_.height_;
    image_ = LoadImage(p, w, h);
}

Tile GridTileSet::GetTile(int id) const
{
    auto nCols = tileSet_.dimensions_.columns_;
    auto tileW = tileSet_.dimensions_.tileWidth_;
    auto tileH = tileSet_.dimensions_.tileHeight_;

    auto column = id % nCols;
    auto row = id / nCols;
    auto u = column * tileW;
    auto v = row * tileH;
    sf::IntRect uvRect = sf::IntRect(u, v, tileW, tileH);

    Tile t;
    t.image_.texture_ = image_.texture_;
    t.image_.size_ = sf::Vector2i(tileW, tileH);
    t.image_.uvRect_ = uvRect;

    return t;
}

}  // namespace Tile

}  // namespace FA
