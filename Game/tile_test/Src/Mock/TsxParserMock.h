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
    MOCK_METHOD(bool, Parse, (DocumentT & xmlDocument, const std::string& xmlBuffer, ParsedTsx& parsedTsx),
                (const override));
};

template <class DocumentT, class ElementT, class ErrorT>
class TsxParserMockProxy : public BasicTsxParser<DocumentT, ElementT, ErrorT>
{
public:
    TsxParserMockProxy(TsxParserMock<DocumentT, ElementT, ErrorT>& mock)
        : mock_(mock)
    {}

    bool Parse(DocumentT& xmlDocument, const std::string& xmlBuffer, ParsedTsx& parsedTsx) const override
    {
        return mock_.Parse(xmlDocument, xmlBuffer, parsedTsx);
    }

private:
    TsxParserMock<DocumentT, ElementT, ErrorT>& mock_;
};

}  // namespace Tile

}  // namespace FA
