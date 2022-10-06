/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GridTileSet.h"

#include "TileHelper.h"

namespace FA {

namespace Tile {

GridTileSet::GridTileSet(const std::string &tsxDir, const std::string &textureFilePath, const Dimensions &dimensions)
    : BasicTileSet()
    , dimensions_(dimensions)
{
    p_ = GetFilePath(tsxDir, textureFilePath);
}

GridTileSet::~GridTileSet() = default;

TileSetData GridTileSet::GenerateTileData() const
{
    auto nCols = dimensions_.columns_;
    auto nRows = dimensions_.tileCount_ / dimensions_.columns_;
    std::vector<Image> images;
    images.push_back({p_, nCols, nRows});

    std::unordered_map<int, FrameData> lookupTable;

    auto w = dimensions_.tileWidth_;
    auto h = dimensions_.tileHeight_;

    for (unsigned int id = 0; id < dimensions_.tileCount_; id++) {
        auto column = id % nCols;
        auto row = id / nCols;
        Frame frame = {p_, column, row, w, h};
        lookupTable[id] = FrameData{frame, {}};
    }

    return {images, lookupTable};
}

}  // namespace Tile

}  // namespace FA
