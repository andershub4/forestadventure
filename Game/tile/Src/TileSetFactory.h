/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ParsedElements.h"

namespace FA {

namespace Tile {

class BasicTileSet;

class TileSetFactory
{
public:
    TileSetFactory();
    virtual ~TileSetFactory();

    std::unique_ptr<BasicTileSet> Create(const std::string &tsxDir, const std::vector<ParsedTile> &tiles,
                                         const ParsedTileSet &tileSet, const std::string &imageSource) const;
};

}  // namespace Tile

}  // namespace FA
