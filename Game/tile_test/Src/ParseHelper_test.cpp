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

TEST(ParseHelper, ParseTileSetShouldSucceed)
{
    ParseHelper<XMLElementMock, XMLError> h;
    ParsedTileSetData expected{"tsname", 16, 80, 3, 0};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char**>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.name_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileHeight_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilecount"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("columns"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.columns_), Return(XML_SUCCESS)));

    ParsedTileSetData result;
    EXPECT_EQ(true, (h.ParseTileSet(&mock, result)));
    EXPECT_EQ(expected, result);
}

TEST(ParseHelper, ParseTileSetShouldFailDueToWrongAttributeName)
{
    ParseHelper<XMLElementMock, XMLError> h;
    ParsedTileSetData expected{"tsname", 16, {}, 3, 0};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char**>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.name_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int*>()))
        .WillOnce(Return(XML_WRONG_ATTRIBUTE_TYPE));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilecount"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("columns"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.columns_), Return(XML_SUCCESS)));

    ParsedTileSetData result;
    EXPECT_EQ(false, (h.ParseTileSet(&mock, result)));
    EXPECT_EQ(expected, result);
}

TEST(ParseHelper, ParseTileSetShouldFailDueToNoAttribute)
{
    ParseHelper<XMLElementMock, XMLError> h;
    ParsedTileSetData expected{{}, 16, 0, 3, 0};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char**>())).WillOnce(Return(XML_NO_ATTRIBUTE));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileHeight_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilecount"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("columns"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.columns_), Return(XML_SUCCESS)));

    ParsedTileSetData result;
    EXPECT_EQ(false, (h.ParseTileSet(&mock, result)));
    EXPECT_EQ(expected, result);
}

TEST(ParseHelper, ParseImageShouldSucceed)
{
    ParseHelper<XMLElementMock, XMLError> h;
    ParsedImage expected{"myImage.png", 16, 16};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("source"), An<const char**>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.source_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("width"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("height"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.height_), Return(XML_SUCCESS)));

    ParsedImage result;
    EXPECT_EQ(true, (h.ParseImage(&mock, result)));
    EXPECT_EQ(expected, result);
}

TEST(ParseHelper, ParseTileWithImageShouldSucceed)
{
    ParseHelper<XMLElementMock, XMLError> h;
    ParsedImage expectedImage{"myImage.png", 16, 16};
    ParsedTile expected{110, expectedImage};
    XMLElementMock mock;
    XMLElementMock imageMock;

    EXPECT_CALL(mock, QueryAttribute(StrEq("id"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageMock));

    EXPECT_CALL(imageMock, QueryStringAttribute(StrEq("source"), An<const char**>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage.source_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock, QueryAttribute(StrEq("width"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock, QueryAttribute(StrEq("height"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage.height_), Return(XML_SUCCESS)));

    ParsedTile result;
    EXPECT_EQ(true, (h.ParseTile(&mock, result)));
    EXPECT_EQ(expected, result);
}

TEST(ParseHelper, ParseThreeTilesShouldSucceed)
{
    ParseHelper<XMLElementMock, XMLError> h;
    ParsedImage expectedImage1{"myImage1.png", 16, 16};
    ParsedImage expectedImage2{"myImage2.png", 32, 32};
    ParsedImage expectedImage3{"myImage3.png", 64, 32};
    ParsedTile expected1{110, expectedImage1};
    ParsedTile expected2{111, expectedImage2};
    ParsedTile expected3{112, expectedImage3};
    std::vector<ParsedTile> expected{expected1, expected2, expected3};

    XMLElementMock mock1, mock2, mock3;
    XMLElementMock imageMock1, imageMock2, imageMock3;

    // first
    EXPECT_CALL(mock1, QueryAttribute(StrEq("id"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected1.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock1, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageMock1));

    EXPECT_CALL(imageMock1, QueryStringAttribute(StrEq("source"), An<const char**>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage1.source_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock1, QueryAttribute(StrEq("width"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage1.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock1, QueryAttribute(StrEq("height"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage1.height_), Return(XML_SUCCESS)));

    EXPECT_CALL(mock1, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&mock2));

    // second
    EXPECT_CALL(mock2, QueryAttribute(StrEq("id"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected2.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock2, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageMock2));

    EXPECT_CALL(imageMock2, QueryStringAttribute(StrEq("source"), An<const char**>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage2.source_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock2, QueryAttribute(StrEq("width"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage2.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock2, QueryAttribute(StrEq("height"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage2.height_), Return(XML_SUCCESS)));

    EXPECT_CALL(mock2, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&mock3));

    // third
    EXPECT_CALL(mock3, QueryAttribute(StrEq("id"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected3.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock3, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageMock3));

    EXPECT_CALL(imageMock3, QueryStringAttribute(StrEq("source"), An<const char**>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage3.source_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock3, QueryAttribute(StrEq("width"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage3.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(imageMock3, QueryAttribute(StrEq("height"), An<unsigned int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedImage3.height_), Return(XML_SUCCESS)));

    EXPECT_CALL(mock3, NextSiblingElement(StrEq("tile"))).WillOnce(Return(nullptr));

    std::vector<ParsedTile> result;
    EXPECT_EQ(true, (h.ParseTiles(&mock1, result)));
    EXPECT_EQ(expected, result);
}

}  // namespace Tile

}  // namespace FA
