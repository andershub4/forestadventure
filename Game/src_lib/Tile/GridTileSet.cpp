/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GridTileSet.h"

#include "FrameData.h"
#include "Image.h"
#include "TileHelper.h"

namespace FA {

namespace Tile {

GridTileSet::GridTileSet(const std::string &tsxDir, const std::string &textureFilePath, const Dimensions &dimensions)
    : BasicTileSet()
    , tsxDir_(tsxDir)
    , textureFilePath_(textureFilePath)
    , dimensions_(dimensions)
{}

GridTileSet::~GridTileSet() = default;

void GridTileSet::Create()
{
    p_ = GetFilePath(tsxDir_, textureFilePath_);
}

std::vector<Image> GridTileSet::GetImages() const
{
    auto nCols = dimensions_.columns_;
    auto nRows = dimensions_.tileCount_ / dimensions_.columns_;
    std::vector<Image> images;
    images.push_back({p_, nCols, nRows});

    return images;
}

FrameData GridTileSet::GetFrameData(int id) const
{
    auto nCols = dimensions_.columns_;
    auto w = dimensions_.tileWidth_;
    auto h = dimensions_.tileHeight_;
    auto column = id % nCols;
    auto row = id / nCols;
    Frame frame = {p_, column, row, w, h};
    std::vector<Frame> frames = {frame};

    return FrameData(frames);
}

}  // namespace Tile

}  // namespace FA
