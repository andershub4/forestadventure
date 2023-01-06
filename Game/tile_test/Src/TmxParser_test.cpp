/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <vector>

#include <gtest/gtest.h>

#include "Mock/ParseHelperMock.h"
#include "Mock/TmxLogMock.h"
#include "Mock/XMLMock.h"

#include "TmxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TmxParserTest : public Test
{
protected:
    using ParseResult = ParseResult<XMLErrorMock>;

    TmxParserTest()
        : helperMock_(std::make_shared<ParseHelperMock<XMLElementMock, XMLErrorMock>>())
        , parser_(helperMock_)
    {}

    const std::string xmlBuffer_ = "xml content";

    const ParsedMap map_{"right-down", 100, 100, 16, 16};
    const ParsedTmxTileSet tmxTileSet_{1, "tileset.tsx"};
    const ParsedLayer layer1_{1, "Ground Layer 1", 100, 100, "849, 849, 850"};
    const ParsedLayer layer2_{1, "Ground Layer 2", 100, 100, "149, 149, 150"};
    const ParsedObject object1_{4, "Player", 360, 296, {{"FaceDirection", "Down"}}};
    const ParsedObject object2_{5, "Enemy", 260, 196, {{"FaceDirection", "Down"}}};
    const ParsedObjectGroup group_{2, "ObjectGroup1", {object1_, object2_}};
    const std::vector<ParseResult> parseResult_;

    XMLDocumentMock docMock_;
    XMLElementMock mapElementMock_;

    std::shared_ptr<ParseHelperMock<XMLElementMock, XMLErrorMock>> helperMock_;
    TmxParser<XMLDocumentMock, XMLElementMock, XMLErrorMock> parser_;
    StrictMock<LoggerMock> loggerMock_;
};

TEST_F(TmxParserTest, TestParsedTmxDataEqualToOperator)
{
    ParsedTmx d1{map_, {tmxTileSet_}, {layer1_}, {group_}};
    ParsedTmx d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.map_.height_ = 200;
    EXPECT_FALSE(d1 == d2);
}

TEST_F(TmxParserTest, ParseShouldFailDueToError)
{
    EXPECT_CALL(docMock_, Parse(StrEq(xmlBuffer_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(true));

    ParsedTmx result;
    EXPECT_FALSE(parser_.Parse(docMock_, xmlBuffer_, result));
    ParsedTmx expected;
    EXPECT_EQ(expected, result);
}

TEST_F(TmxParserTest, ParseValidMapShouldSucceed)
{
    EXPECT_CALL(docMock_, Parse(StrEq(xmlBuffer_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock_, FirstChildElement(StrEq("map"))).WillOnce(Return(&mapElementMock_));
    EXPECT_CALL(*helperMock_, ParseMap(&mapElementMock_, _))
        .WillOnce(DoAll(SetArgReferee<1>(map_), Return(parseResult_)));

    XMLElementMock tileSetMock;
    EXPECT_CALL(mapElementMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetMock));
    EXPECT_CALL(*helperMock_, ParseTmxTileSet(&tileSetMock, _))
        .WillOnce(DoAll(SetArgReferee<1>(tmxTileSet_), Return(parseResult_)));
    EXPECT_CALL(tileSetMock, NextSiblingElement(StrEq("tileset"))).WillOnce(Return(nullptr));

    XMLElementMock layerMock1;
    EXPECT_CALL(mapElementMock_, FirstChildElement(StrEq("layer"))).WillOnce(Return(&layerMock1));
    EXPECT_CALL(*helperMock_, ParseLayer(&layerMock1, _))
        .WillOnce(DoAll(SetArgReferee<1>(layer1_), Return(parseResult_)));

    XMLElementMock layerMock2;
    EXPECT_CALL(layerMock1, NextSiblingElement(StrEq("layer"))).WillOnce(Return(&layerMock2));
    EXPECT_CALL(*helperMock_, ParseLayer(&layerMock2, _))
        .WillOnce(DoAll(SetArgReferee<1>(layer2_), Return(parseResult_)));

    EXPECT_CALL(layerMock2, NextSiblingElement(StrEq("layer"))).WillOnce(Return(nullptr));

    XMLElementMock groupMock;
    EXPECT_CALL(mapElementMock_, FirstChildElement(StrEq("objectgroup"))).WillOnce(Return(&groupMock));
    EXPECT_CALL(*helperMock_, ParseObjectGroup(&groupMock, _))
        .WillOnce(DoAll(SetArgReferee<1>(group_), Return(parseResult_)));
    EXPECT_CALL(groupMock, NextSiblingElement(StrEq("objectgroup"))).WillOnce(Return(nullptr));

    ParsedTmx result;
    EXPECT_TRUE(parser_.Parse(docMock_, xmlBuffer_, result));
    ParsedTmx expected{map_, {tmxTileSet_}, {layer1_, layer2_}, {group_}};
    EXPECT_EQ(expected, result);
}

}  // namespace Tile

}  // namespace FA
