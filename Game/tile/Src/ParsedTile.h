/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "ParsedImage.h"

namespace FA {

namespace Tile {

struct ParsedTile
{
    unsigned int id_{};
    ParsedImage image_;
};

inline bool operator==(const ParsedTile& lhs, const ParsedTile& rhs)
{
    return lhs.id_ == rhs.id_ && lhs.image_ == rhs.image_;
}

}  // namespace Tile

}  // namespace FA
