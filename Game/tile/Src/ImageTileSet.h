/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "TileSetIf.h"

#include "ParsedElements.h"

namespace FA {

namespace Tile {

class ImageTileSet : public TileSetIf
{
public:
    ImageTileSet(const std::string &tsxDir, const std::vector<ParsedTile> &parsedTiles);

    virtual TileSetData GenerateTileData() const override;

private:
    std::vector<ParsedTile> parsedTiles_;
    std::string tsxDir_{};
};

}  // namespace Tile

}  // namespace FA
