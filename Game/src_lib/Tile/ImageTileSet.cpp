/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageTileSet.h"

namespace FA {

namespace Tile {

ImageTileSet::ImageTileSet(const TileMapData::TileSet &tileSet, TextureManager &textureManager)
    : BasicTileSet(textureManager)
    , tileSet_(tileSet)
{}

ImageTileSet::~ImageTileSet() = default;

void ImageTileSet::Load()
{
    for (const auto &tile : tileSet_.tiles_) {
        Tile t;
        auto id = tile.id_;
        auto p = tile.image_.textureFilePath_;
        auto w = tile.image_.width_;
        auto h = tile.image_.height_;
        t.image_ = LoadImage(p, w, h);
        tiles_[id] = t;
    }

    for (const auto &tile : tileSet_.tiles_) {
        auto id = tile.id_;
        auto animation = tile.animation_;
        auto frames = animation.frames_;

        if (!frames.empty()) {
            Animation animation;
            for (auto frame : frames) {
                Animation::Frame f;
                auto id = frame.tileId_;
                f.texture_ = tiles_.at(id).image_.texture_;
                f.uvRect_ = tiles_.at(id).image_.uvRect_;
                f.switchTime_ = frame.duration_ / 1000.0f;
                animation.frames_.push_back(f);
            }
            tiles_[id].animation = animation;
        }
    }
}

Tile ImageTileSet::GetTile(int id) const
{
    return tiles_.at(id);
}

}  // namespace Tile

}  // namespace FA
