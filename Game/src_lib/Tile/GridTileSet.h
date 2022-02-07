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

class GridTileSet : public BasicTileSet
{
public:
    GridTileSet(const TileMapData::TileSet &tileSet, SheetManager &sheetManager);
    virtual ~GridTileSet();

    virtual void Load() override;
    virtual Tile GetTile(int id) const override;

private:
    TileMapData::TileSet tileSet_;
    Image image_;
};

}  // namespace Tile

}  // namespace FA
