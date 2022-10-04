/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "ParsedElements.h"

namespace FA {

namespace Tile {

template <class ElementT, class ErrorT>
class BasicParseHelper
{
public:
    virtual ~BasicParseHelper() = default;

    virtual std::vector<ParseResult<ErrorT>> ParseMap(ElementT* element, ParsedMap& map) const = 0;
    virtual std::vector<ParseResult<ErrorT>> ParseTmxTileSet(ElementT* element, ParsedTmxTileSet& tileSet) const = 0;
    virtual std::vector<ParseResult<ErrorT>> ParseLayer(ElementT* element, ParsedLayer& layer) const = 0;
    virtual std::vector<ParseResult<ErrorT>> ParseObjectGroup(ElementT* element, ParsedObjectGroup& group) const = 0;
    virtual std::vector<ParseResult<ErrorT>> ParseTileSet(ElementT* element, ParsedTileSet& tileSet) const = 0;
    virtual std::vector<ParseResult<ErrorT>> ParseImage(ElementT* element, ParsedImage& image) const = 0;
    virtual std::vector<ParseResult<ErrorT>> ParseTile(ElementT* element, ParsedTile& tile) const = 0;
};

}  // namespace Tile

}  // namespace FA
