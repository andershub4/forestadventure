/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicTmxParser.h"

namespace FA {

namespace Tile {

template <class DocumentT, class ElementT, class ErrorT>
class TmxParserMock : public BasicTmxParser<DocumentT, ElementT, ErrorT>
{
public:
    MOCK_METHOD(bool, Parse, (DocumentT & xmlDocument, const std::string& xmlBuffer, ParsedTmx& parsedTmx),
                (const override));
};

template <class DocumentT, class ElementT, class ErrorT>
class TmxParserMockProxy : public BasicTmxParser<DocumentT, ElementT, ErrorT>
{
public:
    TmxParserMockProxy(TmxParserMock<DocumentT, ElementT, ErrorT>& mock)
        : mock_(mock)
    {}

    bool Parse(DocumentT& xmlDocument, const std::string& xmlBuffer, ParsedTmx& parsedTmx) const override
    {
        return mock_.Parse(xmlDocument, xmlBuffer, parsedTmx);
    }

private:
    TmxParserMock<DocumentT, ElementT, ErrorT>& mock_;
};

}  // namespace Tile

}  // namespace FA
