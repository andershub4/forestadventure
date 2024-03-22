/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "TileMapData.h"

namespace FA {

namespace Tile {

class TileSetIf
{
public:
    virtual ~TileSetIf() = default;

    virtual TileSetData GenerateTileData() const = 0;
};

}  // namespace Tile

}  // namespace FA
