/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicTileSet.h"

#include "TileMapData.h"

namespace FA {

namespace Tile {

class GridTileSet : public BasicTileSet
{
public:
    GridTileSet(const TileMapData::TileSet &tileSet);
    virtual ~GridTileSet();

    virtual void Create() override {}
    virtual std::vector<Image> GetImages() const override;
    virtual FrameData GetFrameData(int id) const override;

private:
    TileMapData::TileSet tileSet_;
};

}  // namespace Tile

}  // namespace FA
