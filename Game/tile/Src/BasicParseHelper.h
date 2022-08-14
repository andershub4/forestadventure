/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

namespace FA {

namespace Tile {

struct ParsedTileSetData;
struct ParsedImage;
struct ParsedTile;

template <class ElementT, class ErrorT>
class BasicParseHelper
{
public:
    virtual bool ParseTileSet(ElementT* element, ParsedTileSetData& data) const = 0;
    virtual bool ParseImage(ElementT* element, ParsedImage& data) const = 0;
    virtual bool ParseTile(ElementT* element, ParsedTile& data) const = 0;
    virtual bool ParseTiles(ElementT* element, std::vector<ParsedTile>& tiles) const = 0;
};

}  // namespace Tile

}  // namespace FA
