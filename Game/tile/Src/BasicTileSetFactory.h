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

class BasicTileSetFactory
{
public:
    virtual ~BasicTileSetFactory() = default;

    virtual std::unique_ptr<BasicTileSet> Create(const std::string &tsxDir, const std::vector<ParsedTile> &tiles,
                                                 const ParsedTileSet &tileSet,
                                                 const std::string &imageSource) const = 0;
};

}  // namespace Tile

}  // namespace FA
