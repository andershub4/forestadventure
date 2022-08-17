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

template <class DocumentT, class ElementT, class ErrorT>
class ParseHelperMock : BasicParseHelper<DocumentT, ElementT, ErrorT>
{
public:
    MOCK_METHOD(bool, ParseTileSet, (DocumentT * document, ParsedTileSetData& data), (const, override));
    MOCK_METHOD(bool, ParseImage, (ElementT * parentEelement, ParsedImage& image), (const, override));
    MOCK_METHOD(bool, ParseTiles(ElementT* parentElement, std::vector<ParsedTile>& tiles)(const, override));
};

}  // namespace Tile

}  // namespace FA
