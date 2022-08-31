/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicTsxParser.h"

namespace FA {

namespace Tile {

template <class DocumentT, class ElementT, class ErrorT>
class TsxParserMock : public BasicTsxParser<DocumentT, ElementT, ErrorT>
{
public:
    MOCK_METHOD(bool, Parse, (const std::string& fileName, DocumentT* xmlDocument, ParsedTsx& parsedTsx),
                (const, override));
};

}  // namespace Tile

}  // namespace FA
