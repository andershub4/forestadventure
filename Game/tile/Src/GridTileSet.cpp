/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GridTileSet.h"

#include "TileHelper.h"

namespace FA {

namespace Tile {

GridTileSet::GridTileSet(const std::string &tsxDir, const std::string &textureFilePath, const ParsedTileSet &parsedTileSet)
    : BasicTileSet()
    , parsedTileSet_(parsedTileSet)
{
    p_ = GetFilePath(tsxDir, textureFilePath);
}

GridTileSet::~GridTileSet() = default;

TileSetData GridTileSet::GenerateTileData() const
{
    auto nCols = parsedTileSet_.columns_;
    auto nRows = parsedTileSet_.tileCount_ / parsedTileSet_.columns_;
    std::vector<Image> images;
    images.push_back({p_, nCols, nRows});

    std::unordered_map<int, FrameData> lookupTable;

    auto w = parsedTileSet_.tileWidth_;
    auto h = parsedTileSet_.tileHeight_;

    for (unsigned int id = 0; id < parsedTileSet_.tileCount_; id++) {
        auto column = id % nCols;
        auto row = id / nCols;
        Frame frame = {p_, column, row, w, h};
        lookupTable[id] = FrameData{frame, {}};
    }

    return {images, lookupTable};
}

}  // namespace Tile

}  // namespace FA
