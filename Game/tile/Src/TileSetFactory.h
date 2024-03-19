/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "TileSetFactoryIf.h"

namespace FA {

namespace Tile {

class TileSetIf;

class TileSetFactory : public TileSetFactoryIf
{
public:
    TileSetFactory();
    virtual ~TileSetFactory();

    std::unique_ptr<TileSetIf> Create(const std::string &tsxDir, const std::vector<ParsedTile> &tiles,
                                      const ParsedTileSet &tileSet, const std::string &imageSource) const;
};

}  // namespace Tile

}  // namespace FA
