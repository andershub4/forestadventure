/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tinyxml2/tinyxml2.h>

#include "Mock/TmxLoggerMock.h"
#include "ParseHelper.h"

#include "TmxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TmxParserInt : public Test
{
protected:
    using ParseHelperImpl = ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>;

    TmxParserInt()
        : helper_(std::make_shared<ParseHelperImpl>())
        , parser_(helper_)
    {}

    const std::string xmlVersion_ = "<?xml version =\" 1.0 \" encoding=\" UTF - 8 \"?>";
    const std::string xmlStartMap_ =
        "<map version = \"1.8\" tiledversion = \"1.8.1\" orientation = \"orthogonal\" renderorder =\"right-down\" "
        "width = \"3\" height = \"3\" tilewidth = \"16\" tileheight =\"16\" infinite = \"0\" nextlayerid = \"1\" "
        "nextobjectid =\"1\">";
    const std::string xmlEndMap_ = "</map>";

    const std::string xmlTileSet_ =
        "<tileset firstgid = \"1\" source = \"tileset1.tsx\" /> <tileset firstgid = \"500\" source = "
        "\"tileset2.tsx\" />";

    const std::string xmlStartLayer_ = "<layer id = \"1\" name = \"Ground Layer 1\" width =\"3\" height = \"3\">";
    const std::string xmlEndLayer_ = "</layer>";

    const std::string xmlStartObjectGroup_ = "<objectgroup id=\"1\" name=\"Object Layer 1\">";
    const std::string xmlEndObjectGroup_ = "</objectgroup>";

    const std::string xmlStartObject_ = "<object id=\"1\" type=\"Player\" x=\"24\" y=\"48\">";
    const std::string xmlEndObject_ = "</object>";

    const std::string xmlStartProperties_ = "<properties>";
    const std::string xmlEndProperties_ = "</properties>";

    const std::string xmlObjectProperty_ = "<property name=\"Strength\" value=\"4\"/>";

    const std::string xmlLayerStartData_ = "<data encoding = \"csv\">864, 626, 626, 626, 322, 120, 120, 310, 310";
    const std::string xmlLayerEndData_ = "</data>";

    StrictMock<LoggerMock> loggerMock_;
    tinyxml2::XMLDocument doc_;
    std::shared_ptr<ParseHelperImpl> helper_;
    TmxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError> parser_;
};

TEST_F(TmxParserInt, ParseShouldFailDueToEmptyXml)
{
    ParsedTmx parsedTmx;

    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("tinyxml2 error: XML_ERROR_EMPTY_DOCUMENT")));
    bool success = parser_.Parse(doc_, "", parsedTmx);

    ParsedTmx expected{};

    EXPECT_FALSE(success);
    EXPECT_THAT(parsedTmx, Eq(expected));
}

TEST_F(TmxParserInt, ParseShouldFailDueToWrongXmlContent)
{
    ParsedTmx parsedTmx;
    const std::string s = "<br></br>";

    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("Error while parsing: map element does not exist")));
    bool success = parser_.Parse(doc_, s, parsedTmx);

    ParsedTmx expected{};

    EXPECT_FALSE(success);
    EXPECT_THAT(parsedTmx, Eq(expected));
}

TEST_F(TmxParserInt, ParseShouldFailDueToNoEndMapTag)
{
    ParsedTmx parsedTmx;
    std::stringstream ss;
    ss << xmlVersion_ << xmlStartMap_ << xmlTileSet_;

    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("tinyxml2 error: XML_ERROR_PARSING")));
    bool success = parser_.Parse(doc_, ss.str(), parsedTmx);

    ParsedTmx expected{};

    EXPECT_FALSE(success);
    EXPECT_THAT(parsedTmx, Eq(expected));
}

TEST_F(TmxParserInt, ParseValidMapShouldSucceed)
{
    ParsedTmx parsedTmx;
    std::stringstream ss;
    ss << xmlVersion_ << xmlStartMap_ << xmlTileSet_ << xmlStartLayer_ << xmlLayerStartData_ << xmlLayerEndData_
       << xmlEndLayer_ << xmlStartObjectGroup_ << xmlStartObject_ << xmlStartProperties_ << xmlObjectProperty_
       << xmlEndProperties_ << xmlEndObject_ << xmlEndObjectGroup_ << xmlEndMap_;
    bool success = parser_.Parse(doc_, ss.str(), parsedTmx);

    ParsedMap expectedMap{"right-down", 3, 3, 16, 16};
    ParsedTmx expected{expectedMap,
                       {{1, "tileset1.tsx"}, {500, "tileset2.tsx"}},
                       {{1, "Ground Layer 1", 3, 3, "864, 626, 626, 626, 322, 120, 120, 310, 310"}},
                       {{1, "Object Layer 1", {{1, "Player", 24, 48, {{"Strength", "4"}}}}}}};

    EXPECT_TRUE(success);
    EXPECT_THAT(parsedTmx, Eq(expected));
}

}  // namespace Tile

}  // namespace FA
