/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "Mock/XMLMock.h"
#include "ParseHelperIf.h"

namespace FA {

namespace Tile {

class ParseHelperMock : public ParseHelperIf<XMLElementMock, XMLErrorMock>
{
public:
    MOCK_METHOD((std::vector<ParseResult<XMLErrorMock>>), ParseMap, (XMLElementMock * element, ParsedMap& map),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<XMLErrorMock>>), ParseTmxTileSet,
                (XMLElementMock * element, ParsedTmxTileSet& tileSet), (const, override));
    MOCK_METHOD((std::vector<ParseResult<XMLErrorMock>>), ParseLayer, (XMLElementMock * element, ParsedLayer& layer),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<XMLErrorMock>>), ParseObjectGroup,
                (XMLElementMock * element, ParsedObjectGroup& group), (const, override));
    MOCK_METHOD((std::vector<ParseResult<XMLErrorMock>>), ParseTileSet,
                (XMLElementMock * element, ParsedTileSet& tileSet), (const, override));
    MOCK_METHOD((std::vector<ParseResult<XMLErrorMock>>), ParseImage, (XMLElementMock * element, ParsedImage& image),
                (const, override));
    MOCK_METHOD((std::vector<ParseResult<XMLErrorMock>>), ParseTile, (XMLElementMock * element, ParsedTile& tile),
                (const, override));
};

}  // namespace Tile

}  // namespace FA
