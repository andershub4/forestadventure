/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tinyxml2/tinyxml2.h>
#include "ParseHelper.h"

#include "TmxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TmxParserInt : public Test
{
protected:
    using ParseResult = ParseResult<tinyxml2::XMLError>;

    TmxParserInt()
        : helper_(std::make_shared<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>>())
        , parser_(helper_)
    {}

    const std::string xmlBuffer_ =
        "<?xml version =\" 1.0 \" encoding=\" UTF - 8 \"?>\
                                   < map version = \"1.8\" tiledversion = \"1.8.1\" orientation = \"orthogonal\" renderorder =\
                                       \"right-down\" width = \"100\" height = \"100\" tilewidth = \"16\" tileheight =\
                                           \"16\" infinite = \"0\" nextlayerid = \"11\" nextobjectid =\
                                               \"9\" >\
        <tileset firstgid = \"1\" source = \"tileset.tsx\" /> <tileset firstgid = \"1089\" source = \"simplewater.tsx\" />\
        </map>";
    tinyxml2::XMLDocument doc_;
    std::shared_ptr<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>> helper_;
    TmxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError> parser_;
};

TEST_F(TmxParserInt, ParseValidMapShouldSucceed)
{
    ParsedTmx parsedTmx;
    parser_.Parse(doc_, xmlBuffer_, parsedTmx);

    EXPECT_FALSE(parsedTmx.tileSets_.empty());
}

}  // namespace Tile

}  // namespace FA
