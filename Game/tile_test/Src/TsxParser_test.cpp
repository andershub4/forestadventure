/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <vector>

#include <gtest/gtest.h>

#include "Mock/ParseHelperMock.h"
#include "Mock/TmxLoggerMock.h"
#include "Mock/XMLMock.h"

#include "TsxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TsxParserTest : public Test
{
protected:
    using ParseResult = ParseResult<XMLErrorMock>;

    TsxParserTest()
        : helperMock_(std::make_shared<StrictMock<ParseHelperMock>>())
        , parser_(helperMock_)
    {}

    const std::string xmlBuffer_ = "xml content";

    const ParsedTileSet tileSet_{"tsname", 16, 80, 3, 0};
    const ParsedImage image_{"myImage1.png", 16, 16};
    const ParsedAnimation animation1_{{{0, 20}, {1, 20}, {1, 20}}};
    const ParsedAnimation animation2_{{{0, 20}, {1, 20}, {1, 20}}};
    const ParsedAnimation animation3_{{}};
    const ParsedTile tile1_{110, image_, animation1_};
    const ParsedTile tile2_{111, image_, animation2_};
    const ParsedTile tile3_{111, image_, animation3_};
    const std::vector<ParseResult> parseResult_;

    StrictMock<XMLDocumentMock> docMock_;
    StrictMock<XMLElementMock> tileSetElementMock_;
    std::shared_ptr<StrictMock<ParseHelperMock>> helperMock_;
    TsxParser<XMLDocumentMock, XMLElementMock, XMLErrorMock> parser_;
    StrictMock<LoggerMock> loggerMock_;
};

TEST_F(TsxParserTest, TestParsedTsxDataEqualToOperator)
{
    ParsedTsx d1{tileSet_, image_, {tile1_, tile2_, tile3_}};
    ParsedTsx d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.tileSet_.name_ = "newname";
    EXPECT_FALSE(d1 == d2);
}

TEST_F(TsxParserTest, ParseShouldFailDueToError)
{
    EXPECT_CALL(docMock_, Parse(StrEq(xmlBuffer_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(true));
    EXPECT_CALL(docMock_, ErrorName()).WillOnce(Return("XML_ERROR_EMPTY_DOCUMENT"));
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("tinyxml2 error: XML_ERROR_EMPTY_DOCUMENT")));

    ParsedTsx result;
    EXPECT_FALSE(parser_.Parse(docMock_, xmlBuffer_, result));
    ParsedTsx expected;
    EXPECT_EQ(expected, result);
}

TEST_F(TsxParserTest, ParseValidImageDataShouldSucceed)
{
    EXPECT_CALL(docMock_, Parse(StrEq(xmlBuffer_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetElementMock_));
    EXPECT_CALL(*helperMock_, ParseTileSet(&tileSetElementMock_, _))
        .WillOnce(DoAll(SetArgReferee<1>(tileSet_), Return(parseResult_)));

    XMLElementMock tileMock1;
    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("tile"))).WillOnce(Return(&tileMock1));
    EXPECT_CALL(*helperMock_, ParseTile(&tileMock1, _)).WillOnce(DoAll(SetArgReferee<1>(tile1_), Return(parseResult_)));

    XMLElementMock tileMock2;
    EXPECT_CALL(tileMock1, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&tileMock2));
    EXPECT_CALL(*helperMock_, ParseTile(&tileMock2, _)).WillOnce(DoAll(SetArgReferee<1>(tile2_), Return(parseResult_)));

    XMLElementMock tileMock3;
    EXPECT_CALL(tileMock2, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&tileMock3));
    EXPECT_CALL(*helperMock_, ParseTile(&tileMock3, _)).WillOnce(DoAll(SetArgReferee<1>(tile3_), Return(parseResult_)));

    EXPECT_CALL(tileMock3, NextSiblingElement(StrEq("tile"))).WillOnce(Return(nullptr));

    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("image"))).WillOnce(Return(nullptr));

    ParsedTsx result;
    EXPECT_TRUE(parser_.Parse(docMock_, xmlBuffer_, result));
    ParsedTsx expected{tileSet_, {}, {tile1_, tile2_, tile3_}};
    EXPECT_EQ(expected, result);
}

TEST_F(TsxParserTest, ParseValidGridDataShouldSucceed)
{
    EXPECT_CALL(docMock_, Parse(StrEq(xmlBuffer_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetElementMock_));
    EXPECT_CALL(*helperMock_, ParseTileSet(&tileSetElementMock_, _))
        .WillOnce(DoAll(SetArgReferee<1>(tileSet_), Return(parseResult_)));

    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("tile"))).WillOnce(Return(nullptr));

    XMLElementMock imageElementMock;
    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageElementMock));
    EXPECT_CALL(*helperMock_, ParseImage(&imageElementMock, _))
        .WillOnce(DoAll(SetArgReferee<1>(image_), Return(parseResult_)));

    ParsedTsx result;
    EXPECT_TRUE(parser_.Parse(docMock_, xmlBuffer_, result));
    ParsedTsx expected{tileSet_, image_, {}};
    EXPECT_EQ(expected, result);
}

}  // namespace Tile

}  // namespace FA
