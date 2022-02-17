/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageTileSet.h"

#include "FrameData.h"
#include "Resource/Frame.h"

namespace FA {

namespace Tile {

ImageTileSet::ImageTileSet(const TileMapData::TileSet &tileSet, SheetManager &sheetManager)
    : BasicTileSet(sheetManager)
    , tileSet_(tileSet)
{}

ImageTileSet::~ImageTileSet() = default;

void ImageTileSet::Load()
{
    for (const auto &tile : tileSet_.tiles_) {
        auto id = tile.id_;
        auto p = tile.image_.textureFilePath_;
        LoadSheet(p, sf::Vector2u(1, 1));
        auto frame = GetFrame(p, {0, 0});
        frameData_[id].frame_ = frame;
    }
    for (const auto &tile : tileSet_.tiles_) {
        auto id = tile.id_;
        auto animation = tile.animation_;
        auto frames = animation.frames_;

        if (!frames.empty()) {
            std::vector<Frame> f;
            for (auto frame : frames) {
                auto id = frame.tileId_;
                auto texture = frameData_.at(id).frame_.texture_;
                auto uvRect_ = frameData_.at(id).frame_.rect_;
                f.push_back(Frame(texture, uvRect_));
            }
            frameData_.at(id).frames_ = f;
        }
    }
}

FrameData ImageTileSet::GetFrameData(int id) const
{
    return frameData_.at(id);
}

}  // namespace Tile

}  // namespace FA
