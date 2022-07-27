/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GridTileSet.h"

#include "FrameData.h"

namespace FA {

namespace Tile {

GridTileSet::GridTileSet(const TileMapData::TileSet &tileSet)
    : BasicTileSet()
    , tileSet_(tileSet)
{}

GridTileSet::~GridTileSet() = default;

std::vector<BasicTileSet::Image> GridTileSet::GetImages() const
{
    auto p = tileSet_.image_.textureFilePath_;
    auto nCols = tileSet_.dimensions_.columns_;
    auto nRows = tileSet_.dimensions_.tileCount_ / tileSet_.dimensions_.columns_;
    std::vector<BasicTileSet::Image> images;
    images.push_back({p, nCols, nRows});

    return images;
}

FrameData GridTileSet::GetFrameData(int id) const
{
    auto nCols = tileSet_.dimensions_.columns_;
    auto w = tileSet_.dimensions_.tileWidth_;
    auto h = tileSet_.dimensions_.tileHeight_;
    auto column = id % nCols;
    auto row = id / nCols;
    auto p = tileSet_.image_.textureFilePath_;
    Frame frame = {p, column, row, w, h};
    std::vector<Frame> frames = {frame};

    return FrameData(frames);
}

}  // namespace Tile

}  // namespace FA
