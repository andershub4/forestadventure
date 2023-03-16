/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GridTileSet.h"

#include "TileHelper.h"

namespace FA {

namespace Tile {

GridTileSet::GridTileSet(const std::string &tsxDir, const std::string &textureFilePath,
                         const ParsedTileSet &parsedTileSet)
    : BasicTileSet()
    , parsedTileSet_(parsedTileSet)
{
    p_ = GetFilePath(tsxDir, textureFilePath);
}

GridTileSet::~GridTileSet() = default;

TileSetData GridTileSet::GenerateTileData() const
{
    auto nCount = parsedTileSet_.tileCount_;
    auto nCols = parsedTileSet_.columns_;
    std::vector<Image> images;
    std::unordered_map<int, TileData> lookupTable;

    if (nCount == 0 || nCols == 0) {
        images.push_back({p_, 0, 0});
    }
    else {
        if (nCount > maxTileCount_) {
            images.push_back({p_, 0, 0});
        }
        else {
            auto nRows = nCount / nCols;
            images.push_back({p_, nCols, nRows});
            auto w = parsedTileSet_.tileWidth_;
            auto h = parsedTileSet_.tileHeight_;

            for (unsigned int id = 0; id < nCount; id++) {
                auto column = id % nCols;
                auto row = id / nCols;
                Frame frame = {p_, column, row, w, h};
                lookupTable[id] = TileData{frame, {}};
            }
        }
    }

    return {images, lookupTable};
}

}  // namespace Tile

}  // namespace FA
