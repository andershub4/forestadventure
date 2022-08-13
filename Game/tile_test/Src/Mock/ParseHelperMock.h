/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicParseHelper.h"

namespace FA {

namespace Tile {

struct TileSetData;

template <class ElementT, class ErrorT>
class ParseHelperMock : BasicParseHelper<ElementT, ErrorT>
{
public:
    MOCK_METHOD(bool, ParseTileSet, (ElementT * element, TileSetData& data), (const, override));
};

}  // namespace Tile

}  // namespace FA
