/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <vector>

#include <gtest/gtest.h>

#include "Mock/XMLMock.h"

#include "ParseHelper.h"

using namespace testing;

namespace FA {

namespace Tile {

class ParseHelperTest : public testing::Test
{
protected:
    XMLDocumentMock docMock_;
    XMLElementMock tileSetMock_;
    ParseHelper<XMLDocumentMock, XMLElementMock, XMLError> helper_;

protected:
    void ExpectParseImage(XMLElementMock *parentMock, XMLElementMock *mock, const ParsedImage &expected) const;
};

void ParseHelperTest::ExpectParseImage(XMLElementMock *parentMock, XMLElementMock *mock,
                                       const ParsedImage &expected) const
{
    EXPECT_CALL(*parentMock, FirstChildElement(StrEq("image"))).WillOnce(Return(mock));

    EXPECT_CALL(*mock, QueryStringAttribute(StrEq("source"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.source_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("width"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("height"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.height_), Return(XML_SUCCESS)));
}

TEST_F(ParseHelperTest, ParseTileSetShouldSucceed)
{
    ParsedTileSetData expected{"tsname", 16, 80, 3, 0};
    XMLElementMock mock;

    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&mock));

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.name_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileHeight_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilecount"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("columns"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.columns_), Return(XML_SUCCESS)));

    ParsedTileSetData result;
    EXPECT_EQ(true, (helper_.ParseTileSet(&docMock_, result)));
    EXPECT_EQ(expected, result);
}

TEST_F(ParseHelperTest, ParseTileSetShouldFailDueToWrongAttributeName)
{
    ParsedTileSetData expected{"tsname", 16, {}, 3, 0};
    XMLElementMock mock;

    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&mock));

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.name_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int *>()))
        .WillOnce(Return(XML_WRONG_ATTRIBUTE_TYPE));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilecount"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("columns"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.columns_), Return(XML_SUCCESS)));

    ParsedTileSetData result;
    EXPECT_EQ(false, (helper_.ParseTileSet(&docMock_, result)));
    EXPECT_EQ(expected, result);
}

TEST_F(ParseHelperTest, ParseTileSetShouldFailDueToNoAttribute)
{
    ParsedTileSetData expected{{}, 16, 0, 3, 0};
    XMLElementMock mock;

    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&mock));

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char **>())).WillOnce(Return(XML_NO_ATTRIBUTE));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileHeight_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilecount"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("columns"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.columns_), Return(XML_SUCCESS)));

    ParsedTileSetData result;
    EXPECT_EQ(false, (helper_.ParseTileSet(&docMock_, result)));
    EXPECT_EQ(expected, result);
}

TEST_F(ParseHelperTest, ParseImageShouldSucceed)
{
    XMLElementMock parentMock;
    ParsedImage expected{"myImage.png", 16, 16};
    XMLElementMock mock;
    ExpectParseImage(&parentMock, &mock, expected);

    ParsedImage result;
    EXPECT_EQ(true, (helper_.ParseImage(&parentMock, result)));
    EXPECT_EQ(expected, result);
}

TEST_F(ParseHelperTest, ParseThreeTilesShouldSucceed)
{
    ParsedImage expectedImage1{"myImage1.png", 16, 16};
    ParsedImage expectedImage2{"myImage2.png", 32, 32};
    ParsedImage expectedImage3{"myImage3.png", 64, 32};
    ParsedTile expected1{110, expectedImage1};
    ParsedTile expected2{111, expectedImage2};
    ParsedTile expected3{112, expectedImage3};
    std::vector<ParsedTile> expected{expected1, expected2, expected3};

    XMLElementMock parentMock;
    XMLElementMock mock1, mock2, mock3;
    XMLElementMock imageMock1, imageMock2, imageMock3;

    EXPECT_CALL(parentMock, FirstChildElement(StrEq("tile"))).WillOnce(Return(&mock1));

    // first
    EXPECT_CALL(mock1, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected1.id_), Return(XML_SUCCESS)));
    ExpectParseImage(&mock1, &imageMock1, expectedImage1);

    EXPECT_CALL(mock1, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&mock2));

    // second
    EXPECT_CALL(mock2, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected2.id_), Return(XML_SUCCESS)));
    ExpectParseImage(&mock2, &imageMock2, expectedImage2);

    EXPECT_CALL(mock2, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&mock3));

    // third
    EXPECT_CALL(mock3, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected3.id_), Return(XML_SUCCESS)));
    ExpectParseImage(&mock3, &imageMock3, expectedImage3);

    EXPECT_CALL(mock3, NextSiblingElement(StrEq("tile"))).WillOnce(Return(nullptr));

    std::vector<ParsedTile> result;
    EXPECT_EQ(true, (helper_.ParseTiles(&parentMock, result)));
    EXPECT_EQ(expected, result);
}

}  // namespace Tile

}  // namespace FA
