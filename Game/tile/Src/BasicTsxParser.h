/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "ParsedElements.h"

namespace FA {

namespace Tile {

struct ParsedTsx
{
    ParsedTileSet tileSet_;
    ParsedImage image_;
    std::vector<ParsedTile> tiles_;
};

inline bool operator==(const ParsedTsx& lhs, const ParsedTsx& rhs)
{
    return std::tie(lhs.image_, lhs.tileSet_, lhs.tiles_) == std::tie(rhs.image_, rhs.tileSet_, rhs.tiles_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedTsx& p)
{
    os << "tileSet: " << p.tileSet_ << " image: " << p.image_ << " tiles: " << p.tiles_;

    return os;
}

template <class DocumentT, class ElementT, class Error>
class BasicTsxParser
{
public:
    virtual ~BasicTsxParser() = default;

    virtual bool Parse(const std::string& xmlBuffer, ParsedTsx& parsedTsx) const = 0;
};

}  // namespace Tile

}  // namespace FA
