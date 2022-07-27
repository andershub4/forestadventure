/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>

#include "BasicTileSet.h"

#include "TileMapData.h"

namespace FA {

namespace Tile {

class ImageTileSet : public BasicTileSet
{
public:
    ImageTileSet(const TileMapData::TileSet &tileSet);
    virtual ~ImageTileSet();

    virtual void Create() override;
    virtual std::vector<Image> GetImages() const override;
    virtual FrameData GetFrameData(int id) const override;

private:
    TileMapData::TileSet tileSet_;
    std::unordered_map<int, FrameData> frameData_;
};

}  // namespace Tile

}  // namespace FA
