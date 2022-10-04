/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicParseHelper.h"

namespace FA {

namespace Tile {

template <class ElementT, class ErrorT>
class ParseHelperMock : public BasicParseHelper<ElementT, ErrorT>
{
public:
    MOCK_METHOD((std::vector<ParseResult<ErrorT>>), ParseMap, (ElementT * element, ParsedMap& map), (const, override));
    MOCK_METHOD((std::vector<ParseResult<ErrorT>>), ParseTmxTileSet, (ElementT * element, ParsedTmxTileSet& tileSet),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<ErrorT>>), ParseLayer, (ElementT * element, ParsedLayer& layer),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<ErrorT>>), ParseObjectGroup, (ElementT * element, ParsedObjectGroup& group),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<ErrorT>>), ParseTileSet, (ElementT * element, ParsedTileSet& tileSet),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<ErrorT>>), ParseImage, (ElementT * element, ParsedImage& image),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<ErrorT>>), ParseTile, (ElementT * element, ParsedTile& tile),
                (const, override));
};

}  // namespace Tile

}  // namespace FA
