/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>

#include "BasicTileSet.h"

#include "ParsedElements.h"

namespace FA {

namespace Tile {

class ImageTileSet : public BasicTileSet
{
public:
    ImageTileSet(const std::string &tsxDir, const std::vector<ParsedTile> tiles);
    virtual ~ImageTileSet();

    virtual TileSetData CreateTileSetData() const override;

private:
    std::vector<ParsedTile> tiles_;
    std::string tsxDir_{};
};

}  // namespace Tile

}  // namespace FA
