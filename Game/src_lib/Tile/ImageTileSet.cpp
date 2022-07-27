/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageTileSet.h"

#include "FrameData.h"

namespace FA {

namespace Tile {

ImageTileSet::ImageTileSet(const TileMapData::TileSet &tileSet)
    : BasicTileSet()
    , tileSet_(tileSet)
{}

ImageTileSet::~ImageTileSet() = default;

std::vector<BasicTileSet::Image> ImageTileSet::GetImages() const
{
    std::vector<Image> images;

    for (const auto &tile : tileSet_.tiles_) {
        auto id = tile.id_;
        auto p = tile.image_.textureFilePath_;
        images.push_back({p, 1, 1});
    }

    return images;
}

void ImageTileSet::Create()
{
    // Create map to be able to fill up frames below
    std::unordered_map<int, Frame> frameMap;
    for (const auto &tile : tileSet_.tiles_) {
        auto id = tile.id_;
        auto p = tile.image_.textureFilePath_;
        auto w = tile.image_.width_;
        auto h = tile.image_.height_;
        Frame frame = {p, 0, 0, w, h};
        frameMap[id] = frame;
    }

    for (const auto &tile : tileSet_.tiles_) {
        if (!tile.animation_.frames_.empty()) {
            auto id = tile.id_;
            std::vector<Frame> frames;
            for (auto frame : tile.animation_.frames_) {
                auto id = frame.tileId_;
                auto f = frameMap.at(id);
                frames.push_back(f);
            }
            frameData_[id] = FrameData(frames);
        }
    }
}

FrameData ImageTileSet::GetFrameData(int id) const
{
    return frameData_.at(id);
}

}  // namespace Tile

}  // namespace FA
