/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>
#include <vector>

#include "TileMapData.h"

namespace FA {

namespace Tile {

class BasicTileSet
{
public:
    BasicTileSet();
    virtual ~BasicTileSet();

    virtual TileSetData GenerateTileData() const = 0;
};

}  // namespace Tile

}  // namespace FA
