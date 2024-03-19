/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "TileSetIf.h"

namespace FA {

namespace Tile {

class TileSetMock : public TileSetIf
{
public:
    MOCK_METHOD(TileSetData, GenerateTileData, (), (const, override));
};

}  // namespace Tile

}  // namespace FA
