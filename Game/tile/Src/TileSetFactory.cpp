/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileSetFactory.h"

#include "GridTileSet.h"
#include "ImageTileSet.h"

namespace FA {

namespace Tile {

TileSetFactory::TileSetFactory() = default;

TileSetFactory::~TileSetFactory() = default;

std::unique_ptr<BasicTileSet> TileSetFactory::Create(const std::string &tsxDir, const std::vector<ParsedTile> &tiles,
                                                     const ParsedTileSet &tileSet, const std::string &imageSource) const
{
    std::unique_ptr<BasicTileSet> s = nullptr;

    if (!tiles.empty()) {
        s = std::make_unique<ImageTileSet>(tsxDir, tiles);
    }
    else {
        s = std::make_unique<GridTileSet>(tsxDir, imageSource, tileSet);
    }

    return s;
}

}  // namespace Tile

}  // namespace FA
