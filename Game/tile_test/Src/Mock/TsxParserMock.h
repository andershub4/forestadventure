/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicTsxParser.h"
#include "Mock/XMLMock.h"

namespace FA {

namespace Tile {

class TsxParserMock : public BasicTsxParser<XMLDocumentMock, XMLElementMock, XMLErrorMock>
{
public:
    MOCK_METHOD(bool, Parse, (XMLDocumentMock & xmlDocument, const std::string& xmlBuffer, ParsedTsx& parsedTsx),
                (const override));
};

class TsxParserMockProxy : public BasicTsxParser<XMLDocumentMock, XMLElementMock, XMLErrorMock>
{
public:
    TsxParserMockProxy(TsxParserMock& mock)
        : mock_(mock)
    {}

    bool Parse(XMLDocumentMock& xmlDocument, const std::string& xmlBuffer, ParsedTsx& parsedTsx) const override
    {
        return mock_.Parse(xmlDocument, xmlBuffer, parsedTsx);
    }

private:
    TsxParserMock& mock_;
};

}  // namespace Tile

}  // namespace FA
