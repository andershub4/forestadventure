/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <unordered_map>

#include "BasicTileSet.h"

namespace FA {

namespace Tile {

class GridTileSet : public BasicTileSet
{
public:
    struct Dimensions
    {
        unsigned int tileWidth_{};
        unsigned int tileHeight_{};
        unsigned int columns_{};
        unsigned int tileCount_{};
    };

    GridTileSet(const std::string &tsxDir, const std::string &textureFilePath, const Dimensions &dimensions);
    virtual ~GridTileSet();

    virtual TileSetData GenerateTileData() const override;

private:
    Dimensions dimensions_;
    std::string p_{};
};

}  // namespace Tile

}  // namespace FA
