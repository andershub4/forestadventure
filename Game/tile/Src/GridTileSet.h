/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <unordered_map>

#include "BasicTileSet.h"

#include "ParsedElements.h"

namespace FA {

namespace Tile {

class GridTileSet : public BasicTileSet
{
public:
    GridTileSet(const std::string &tsxDir, const std::string &textureFilePath, const ParsedTileSet &parsedTileSet);
    virtual ~GridTileSet();

    virtual TileSetData GenerateTileData() const override;

private:
    ParsedTileSet parsedTileSet_;
    std::string p_{};
};

}  // namespace Tile

}  // namespace FA
