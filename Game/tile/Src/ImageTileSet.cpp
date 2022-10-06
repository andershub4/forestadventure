/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageTileSet.h"

#include "TileHelper.h"

namespace FA {

namespace Tile {

ImageTileSet::ImageTileSet(const std::string &tsxDir, const std::vector<ParsedTile> tiles)
    : BasicTileSet()
    , tsxDir_(tsxDir)
    , tiles_(tiles)
{}

ImageTileSet::~ImageTileSet() = default;

TileSetData ImageTileSet::GenerateTileData() const
{
    std::vector<Image> images;
    std::unordered_map<int, FrameData> lookupTable;
    std::unordered_map<int, Frame> frameMap;

    for (const auto &tile : tiles_) {
        if (!tile.image_.source_.empty()) {
            auto id = tile.id_;
            auto p = GetFilePath(tsxDir_, tile.image_.source_);
            auto w = tile.image_.width_;
            auto h = tile.image_.height_;
            Frame frame = {p, 0, 0, w, h};
            frameMap[id] = frame;
            images.push_back(Image(p));
        }
    }

    for (const auto &tile : tiles_) {
        auto id = tile.id_;
        std::vector<Frame> frames;
        if (!tile.animation_.frames_.empty()) {
            for (auto frame : tile.animation_.frames_) {
                auto id = frame.id_;
                auto f = frameMap.at(id);
                frames.push_back(f);
            }
        }
        Frame frame = frameMap[id];
        lookupTable[id] = FrameData{frame, frames};
    }

    return {images, lookupTable};
}

}  // namespace Tile

}  // namespace FA
