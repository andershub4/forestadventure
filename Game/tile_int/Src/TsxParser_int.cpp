/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tinyxml2/tinyxml2.h>

#include "Mock/TmxLogMock.h"
#include "ParseHelper.h"

#include "TsxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TsxParserInt : public Test
{
protected:
    TsxParserInt()
        : helper_(std::make_shared<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>>())
        , parser_(helper_)
    {}

    const std::string xmlVersion_ = "<?xml version =\" 1.0 \" encoding=\" UTF - 8 \"?>";
    const std::string xmlStartSet_ =
        "<tileset version = \"1.5\" tiledversion = \"1.5.0\" name = \"tileset\" tilewidth = \"16\" tileheight = \"16\" "
        "tilecount =\"100\" columns = \"10\">";
    const std::string xmlEndSet_ = "</tileset>";

    const std::string xmlImageSrc_ =
        "<image source = \"../game/resources/tilesets/tileset.png\" width =\"160\" height = \"160\"/>";

    StrictMock<LoggerMock> loggerMock_;
    tinyxml2::XMLDocument doc_;
    std::shared_ptr<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>> helper_;
    TsxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError> parser_;
};

TEST_F(TsxParserInt, ParseShouldFailDueToEmptyXml)
{
    ParsedTsx parsedTsx;

    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("tinyxml2 error: XML_ERROR_EMPTY_DOCUMENT")));
    bool success = parser_.Parse(doc_, "", parsedTsx);

    ParsedTsx expected{};

    EXPECT_FALSE(success);
    EXPECT_THAT(parsedTsx, Eq(expected));
}

TEST_F(TsxParserInt, ParseShouldFailDueToWrongXmlContent)
{
    ParsedTsx parsedTsx;
    const std::string s = "<br></br>";

    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("Error while parsing: tileset element does not exist")));
    bool success = parser_.Parse(doc_, s, parsedTsx);

    ParsedTsx expected{};

    EXPECT_FALSE(success);
    EXPECT_THAT(parsedTsx, Eq(expected));
}

TEST_F(TsxParserInt, ParseShouldFailDueToNoEndSetTag)
{
    ParsedTsx parsedTsx;
    std::stringstream ss;
    ss << xmlVersion_ << xmlStartSet_ << xmlImageSrc_;

    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("tinyxml2 error: XML_ERROR_PARSING")));
    bool success = parser_.Parse(doc_, ss.str(), parsedTsx);

    ParsedTsx expected{};

    EXPECT_FALSE(success);
    EXPECT_THAT(parsedTsx, Eq(expected));
}

TEST_F(TsxParserInt, ParseValidSetShouldSucceed)
{
    ParsedTsx parsedTsx;
    std::stringstream ss;
    ss << xmlVersion_ << xmlStartSet_ << xmlImageSrc_ << xmlEndSet_;
    bool success = parser_.Parse(doc_, ss.str(), parsedTsx);

    ParsedTileSet expectedSet{"tileset", 16, 16, 100, 10};
    ParsedTsx expected{expectedSet, {"../game/resources/tilesets/tileset.png", 160, 160}, {}};

    EXPECT_TRUE(success);
    EXPECT_THAT(parsedTsx, Eq(expected));
}

}  // namespace Tile

}  // namespace FA
