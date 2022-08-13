/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Tile {

struct TileSetData
{
    std::string name_{};
    unsigned int tileWidth_{};
    unsigned int tileHeight_{};
    unsigned int tileCount_{};
    unsigned int columns_{};
};

inline bool operator==(const TileSetData& lhs, const TileSetData& rhs)
{
    return lhs.name_ == rhs.name_ && lhs.tileWidth_ == rhs.tileWidth_ && lhs.tileHeight_ == rhs.tileHeight_ &&
           lhs.tileCount_ == rhs.tileCount_ && lhs.columns_ == rhs.columns_;
}

}  // namespace Tile

}  // namespace FA
