/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicTmxParser.h"
#include "Mock/XMLMock.h"

namespace FA {

namespace Tile {

class TmxParserMock : public BasicTmxParser<XMLDocumentMock, XMLElementMock, XMLErrorMock>
{
public:
    MOCK_METHOD(bool, Parse, (XMLDocumentMock & xmlDocument, const std::string& xmlBuffer, ParsedTmx& parsedTmx),
                (const override));
};

class TmxParserMockProxy : public BasicTmxParser<XMLDocumentMock, XMLElementMock, XMLErrorMock>
{
public:
    TmxParserMockProxy(TmxParserMock& mock)
        : mock_(mock)
    {}

    bool Parse(XMLDocumentMock& xmlDocument, const std::string& xmlBuffer, ParsedTmx& parsedTmx) const override
    {
        return mock_.Parse(xmlDocument, xmlBuffer, parsedTmx);
    }

private:
    TmxParserMock& mock_;
};

}  // namespace Tile

}  // namespace FA
