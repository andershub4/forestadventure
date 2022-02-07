/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GridTileSet.h"

#include "Resource/Frame.h"

namespace FA {

namespace Tile {

GridTileSet::GridTileSet(const TileMapData::TileSet &tileSet, SheetManager &sheetManager)
    : BasicTileSet(sheetManager)
    , tileSet_(tileSet)
{}

GridTileSet::~GridTileSet() = default;

void GridTileSet::Load()
{
    auto p = tileSet_.image_.textureFilePath_;
    auto nCols = tileSet_.dimensions_.columns_;
    auto nRows = tileSet_.dimensions_.tileCount_ / tileSet_.dimensions_.columns_;
    LoadSheet(p, sf::Vector2u(nCols, nRows));
}

Tile GridTileSet::GetTile(int id) const
{
    auto nCols = tileSet_.dimensions_.columns_;
    auto column = id % nCols;
    auto row = id / nCols;
    auto frame = GetFrame(sf::Vector2u(column, row));

    Tile t;
    t.image_.texture_ = frame.texture_;
    t.image_.uvRect_ = frame.rect_;
    return t;
}

}  // namespace Tile

}  // namespace FA
