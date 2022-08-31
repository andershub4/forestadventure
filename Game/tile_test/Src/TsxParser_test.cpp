/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <vector>

#include <gtest/gtest.h>

#include "Mock/ParseHelperMock.h"
#include "Mock/XMLMock.h"

#include "TsxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TsxParserTest : public Test
{
protected:
    const std::string fileName_ = "test.txt";

    XMLDocumentMock docMock_;
    XMLElementMock tileSetElementMock_;

    ParseHelperMock<XMLElementMock, XMLError> helperMock_;
    TsxParser<XMLDocumentMock, XMLElementMock, XMLError> parser_{helperMock_};
};

TEST_F(TsxParserTest, TestParsedTsxDataEqualToOperator)
{
    ParsedTileSetData tsd{"tsname", 16, 80, 3, 0};
    ParsedImage i{"myImage1.png", 16, 16};
    ParsedAnimation a1{{{0, 20}, {1, 20}, {1, 20}}};
    ParsedTile t1{110, i, a1};
    ParsedTile t2{111, i, a1};

    ParsedTsx d1{{"tsname", 16, 80, 3, 0}, {}, {t1, t2}};
    ParsedTsx d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.tileSet_.name_ = "newname";
    EXPECT_FALSE(d1 == d2);
}

TEST_F(TsxParserTest, ParseShouldFailDueToError)
{
    EXPECT_CALL(docMock_, LoadFile(StrEq(fileName_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(true));

    ParsedTsx result;
    EXPECT_EQ(false, (parser_.Parse(fileName_, &docMock_, result)));
}

TEST_F(TsxParserTest, ParseValidImageDataShouldSucceed)
{
    EXPECT_CALL(docMock_, LoadFile(StrEq(fileName_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetElementMock_));
    ParsedTileSetData tileSet;
    EXPECT_CALL(helperMock_, ParseTileSet(&tileSetElementMock_, _))
        .WillOnce(DoAll(SetArgReferee<1>(tileSet), Return(true)));

    XMLElementMock tileMock1;
    ParsedTile tile1;
    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("tile"))).WillOnce(Return(&tileMock1));
    EXPECT_CALL(helperMock_, ParseTile(&tileMock1, _)).WillOnce(DoAll(SetArgReferee<1>(tile1), Return(true)));

    XMLElementMock tileMock2;
    ParsedTile tile2;
    EXPECT_CALL(tileMock1, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&tileMock2));
    EXPECT_CALL(helperMock_, ParseTile(&tileMock2, _)).WillOnce(DoAll(SetArgReferee<1>(tile2), Return(true)));

    XMLElementMock tileMock3;
    ParsedTile tile3;
    EXPECT_CALL(tileMock2, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&tileMock3));
    EXPECT_CALL(helperMock_, ParseTile(&tileMock3, _)).WillOnce(DoAll(SetArgReferee<1>(tile3), Return(true)));

    EXPECT_CALL(tileMock3, NextSiblingElement(StrEq("tile"))).WillOnce(Return(nullptr));

    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("image"))).WillOnce(Return(nullptr));

    ParsedTsx result;
    EXPECT_EQ(true, (parser_.Parse(fileName_, &docMock_, result)));
}

TEST_F(TsxParserTest, ParseValidGridDataShouldSucceed)
{
    EXPECT_CALL(docMock_, LoadFile(StrEq(fileName_)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetElementMock_));
    ParsedTileSetData tileSet;
    EXPECT_CALL(helperMock_, ParseTileSet(&tileSetElementMock_, _))
        .WillOnce(DoAll(SetArgReferee<1>(tileSet), Return(true)));

    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("tile"))).WillOnce(Return(nullptr));

    XMLElementMock imageElementMock;
    EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageElementMock));
    ParsedImage image;
    EXPECT_CALL(helperMock_, ParseImage(&imageElementMock, _)).WillOnce(DoAll(SetArgReferee<1>(image), Return(true)));

    ParsedTsx result;
    EXPECT_EQ(true, (parser_.Parse(fileName_, &docMock_, result)));
}

}  // namespace Tile

}  // namespace FA
