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
    void ExpectParseFrame(XMLElementMock *mock, const ParsedFrame &expected) const;
    void ExpectParseAnimation(XMLElementMock *parentMock, XMLElementMock *animationMock,
                              std::vector<XMLElementMock> &frameMocks, const ParsedAnimation &expected) const;
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

void ParseHelperTest::ExpectParseFrame(XMLElementMock *mock, const ParsedFrame &expected) const
{
    EXPECT_CALL(*mock, QueryAttribute(StrEq("tileid"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("duration"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.duration_), Return(XML_SUCCESS)));
}

void ParseHelperTest::ExpectParseAnimation(XMLElementMock *parentMock, XMLElementMock *mock,
                                           std::vector<XMLElementMock> &frameMocks,
                                           const ParsedAnimation &expected) const
{
    EXPECT_CALL(*parentMock, FirstChildElement(StrEq("animation"))).WillOnce(Return(mock));

    auto &frameMock1 = frameMocks.at(0);
    EXPECT_CALL(*mock, FirstChildElement(StrEq("frame"))).WillOnce(Return(&frameMock1));
    ExpectParseFrame(&frameMock1, expected.frames_.at(0));

    auto &frameMock2 = frameMocks.at(1);
    EXPECT_CALL(frameMock1, NextSiblingElement(StrEq("frame"))).WillOnce(Return(&frameMock2));
    ExpectParseFrame(&frameMock2, expected.frames_.at(1));

    auto &frameMock3 = frameMocks.at(2);
    EXPECT_CALL(frameMock2, NextSiblingElement(StrEq("frame"))).WillOnce(Return(&frameMock3));
    ExpectParseFrame(&frameMock3, expected.frames_.at(2));

    EXPECT_CALL(frameMock3, NextSiblingElement(StrEq("frame"))).WillOnce(Return(nullptr));
}

TEST_F(ParseHelperTest, TestParsedTileSetDataEqualToOperator)
{
    ParsedTileSetData d1{"tsname", 16, 80, 3, 0};
    ParsedTileSetData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.name_ = "myname";
    EXPECT_FALSE(d1 == d2);
}

TEST_F(ParseHelperTest, TestParsedImageEqualToOperator)
{
    ParsedImage d1{"myImage.png", 16, 16};
    ParsedImage d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.source_ = "myOtherImage.png";
    EXPECT_FALSE(d1 == d2);
}

TEST_F(ParseHelperTest, TestParsedFrameEqualToOperator)
{
    ParsedFrame d1{0, 10};
    ParsedFrame d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.duration_ = 30;
    EXPECT_FALSE(d1 == d2);
}

TEST_F(ParseHelperTest, TestParsedAnimationEqualToOperator)
{
    ParsedAnimation d1{{{0, 10}, {1, 10}, {2, 10}}};
    ParsedAnimation d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.frames_.erase(d1.frames_.begin() + 1);
    EXPECT_FALSE(d1 == d2);
}

TEST_F(ParseHelperTest, TestParsedTileEqualToOperator)
{
    ParsedImage i{"myImage1.png", 16, 16};
    ParsedAnimation a1{{{0, 20}, {1, 20}, {1, 20}}};
    ParsedTile d1{110, i, a1};
    ParsedTile d2 = d1;
    EXPECT_TRUE(d1 == d2);
    ParsedAnimation a2{{{1, 20}, {1, 20}, {1, 20}}};
    d1.animation_ = a2;
    EXPECT_FALSE(d1 == d2);
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

TEST_F(ParseHelperTest, ParseSingleTileWithOnlyImageShouldSucceed)
{
    ParsedImage expectedImage{"myImage1.png", 16, 16};
    ParsedTile expectedTile{110, expectedImage, {}};
    std::vector<ParsedTile> expected{expectedTile};
    XMLElementMock parentMock;
    XMLElementMock mock1;
    XMLElementMock imageMock1;

    EXPECT_CALL(parentMock, FirstChildElement(StrEq("tile"))).WillOnce(Return(&mock1));

    EXPECT_CALL(mock1, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expectedTile.id_), Return(XML_SUCCESS)));
    ExpectParseImage(&mock1, &imageMock1, expectedImage);
    EXPECT_CALL(mock1, FirstChildElement(StrEq("animation"))).WillOnce(Return(nullptr));

    EXPECT_CALL(mock1, NextSiblingElement(StrEq("tile"))).WillOnce(Return(nullptr));

    std::vector<ParsedTile> result;
    EXPECT_EQ(true, (helper_.ParseTiles(&parentMock, result)));
    EXPECT_EQ(expected, result);
}

TEST_F(ParseHelperTest, ParseThreeTilesWithBothImageAndAnimationShouldSucceed)
{
    ParsedImage expectedImage1{"myImage1.png", 16, 16};
    ParsedImage expectedImage2{"myImage2.png", 32, 32};
    ParsedImage expectedImage3{"myImage3.png", 64, 32};
    ParsedAnimation expectedAnimation1{{{0, 20}, {1, 20}, {1, 20}}};
    ParsedAnimation expectedAnimation2{{{3, 10}, {11, 20}, {1, 20}}};
    ParsedAnimation expectedAnimation3{{{0, 10}, {0, 20}, {1, 20}}};
    ParsedTile expected1{110, expectedImage1, expectedAnimation1};
    ParsedTile expected2{111, expectedImage2, expectedAnimation2};
    ParsedTile expected3{112, expectedImage3, expectedAnimation3};
    std::vector<ParsedTile> expected{expected1, expected2, expected3};

    XMLElementMock parentMock;
    XMLElementMock mock1, mock2, mock3;
    XMLElementMock imageMock1, imageMock2, imageMock3;
    std::vector<XMLElementMock> frameMocks1(expectedAnimation1.frames_.size());
    std::vector<XMLElementMock> frameMocks2(expectedAnimation2.frames_.size());
    std::vector<XMLElementMock> frameMocks3(expectedAnimation3.frames_.size());
    XMLElementMock animationMock1, animationMock2, animationMock3;

    EXPECT_CALL(parentMock, FirstChildElement(StrEq("tile"))).WillOnce(Return(&mock1));

    // first
    EXPECT_CALL(mock1, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected1.id_), Return(XML_SUCCESS)));
    ExpectParseImage(&mock1, &imageMock1, expectedImage1);
    ExpectParseAnimation(&mock1, &animationMock1, frameMocks1, expectedAnimation1);

    EXPECT_CALL(mock1, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&mock2));

    // second
    EXPECT_CALL(mock2, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected2.id_), Return(XML_SUCCESS)));
    ExpectParseImage(&mock2, &imageMock2, expectedImage2);
    ExpectParseAnimation(&mock2, &animationMock2, frameMocks2, expectedAnimation2);

    EXPECT_CALL(mock2, NextSiblingElement(StrEq("tile"))).WillOnce(Return(&mock3));

    // third
    EXPECT_CALL(mock3, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected3.id_), Return(XML_SUCCESS)));
    ExpectParseImage(&mock3, &imageMock3, expectedImage3);
    ExpectParseAnimation(&mock3, &animationMock3, frameMocks3, expectedAnimation3);

    EXPECT_CALL(mock3, NextSiblingElement(StrEq("tile"))).WillOnce(Return(nullptr));

    std::vector<ParsedTile> result;
    EXPECT_EQ(true, (helper_.ParseTiles(&parentMock, result)));
    EXPECT_EQ(expected, result);
}

}  // namespace Tile

}  // namespace FA
