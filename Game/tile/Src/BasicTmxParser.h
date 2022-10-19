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

struct ParsedTmx
{
    ParsedMap map_;
    std::vector<ParsedTmxTileSet> tileSets_;
    std::vector<ParsedLayer> layers_;
    std::vector<ParsedObjectGroup> objectGroups_;
};

inline bool operator==(const ParsedTmx& lhs, const ParsedTmx& rhs)
{
    return std::tie(lhs.map_, lhs.tileSets_, lhs.layers_, lhs.objectGroups_) ==
           std::tie(rhs.map_, rhs.tileSets_, rhs.layers_, rhs.objectGroups_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedTmx& p)
{
    os << "map: " << p.map_ << " tileSets: " << p.tileSets_ << " layers: " << p.layers_
       << " groups: " << p.objectGroups_;

    return os;
}

template <class DocumentT, class ElementT, class ErrorT>
class BasicTmxParser
{
public:
    virtual ~BasicTmxParser() = default;

    virtual bool Parse(DocumentT& xmlDocument, const std::string& xmlBuffer, ParsedTmx& parsedTmx) const = 0;
};

}  // namespace Tile

}  // namespace FA
