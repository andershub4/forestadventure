/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Tile {

struct ParsedTileSetData;

template <class ElementT, class ErrorT>
class BasicParseHelper
{
public:
    virtual bool ParseTileSet(ElementT* element, ParsedTileSetData& data) const = 0;
};

}  // namespace Tile

}  // namespace FA