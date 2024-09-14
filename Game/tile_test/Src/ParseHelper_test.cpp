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
    using ParseResult = ParseResult<XMLErrorMock>;

    ParseHelper<XMLElementMock, XMLErrorMock> helper_;

protected:
    void ExpectParseObject(XMLElementMock *mock, XMLElementMock *propertiesMock, std::vector<XMLElementMock> &propMocks,
                           const ParsedObject &expected) const;
    void ExpectParseRectObject(XMLElementMock *mock, XMLElementMock *propertiesMock,
                               std::vector<XMLElementMock> &propMocks, const ParsedObject &expected) const;
    void ExpectParseImage(XMLElementMock *mock, const ParsedImage &expected) const;
    void ExpectParseFrame(XMLElementMock *mock, const ParsedFrame &expected) const;
    void ExpectParseAnimation(XMLElementMock *parentMock, XMLElementMock *animationMock,
                              std::vector<XMLElementMock> &frameMocks, const ParsedAnimation &expected) const;
};

void ParseHelperTest::ExpectParseObject(XMLElementMock *mock, XMLElementMock *propertiesMock,
                                        std::vector<XMLElementMock> &propMocks, const ParsedObject &expected) const
{
    EXPECT_CALL(*mock, QueryAttribute(StrEq("id"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryStringAttribute(StrEq("type"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.type_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("x"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.x_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("y"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.y_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("width"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(XML_NO_ATTRIBUTE)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("height"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(XML_NO_ATTRIBUTE)));

    EXPECT_CALL(*mock, FirstChildElement(StrEq("properties"))).WillOnce(Return(propertiesMock));

    auto &propMock1 = propMocks.at(0);
    EXPECT_CALL(*propertiesMock, FirstChildElement(StrEq("property"))).WillOnce(Return(&propMock1));

    EXPECT_CALL(propMock1, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(0).first.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(propMock1, QueryStringAttribute(StrEq("value"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(0).second.c_str()), Return(XML_SUCCESS)));

    auto &propMock2 = propMocks.at(1);
    EXPECT_CALL(propMock1, NextSiblingElement(StrEq("property"))).WillOnce(Return(&propMock2));

    EXPECT_CALL(propMock2, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(1).first.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(propMock2, QueryStringAttribute(StrEq("value"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(1).second.c_str()), Return(XML_SUCCESS)));

    EXPECT_CALL(propMock2, NextSiblingElement(StrEq("property"))).WillOnce(Return(nullptr));
}

void ParseHelperTest::ExpectParseRectObject(XMLElementMock *mock, XMLElementMock *propertiesMock,
                                            std::vector<XMLElementMock> &propMocks, const ParsedObject &expected) const
{
    EXPECT_CALL(*mock, QueryAttribute(StrEq("id"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryStringAttribute(StrEq("type"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.type_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("x"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.x_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("y"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.y_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("width"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(*mock, QueryAttribute(StrEq("height"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.height_), Return(XML_SUCCESS)));

    EXPECT_CALL(*mock, FirstChildElement(StrEq("properties"))).WillOnce(Return(propertiesMock));

    auto &propMock1 = propMocks.at(0);
    EXPECT_CALL(*propertiesMock, FirstChildElement(StrEq("property"))).WillOnce(Return(&propMock1));

    EXPECT_CALL(propMock1, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(0).first.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(propMock1, QueryStringAttribute(StrEq("value"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(0).second.c_str()), Return(XML_SUCCESS)));

    auto &propMock2 = propMocks.at(1);
    EXPECT_CALL(propMock1, NextSiblingElement(StrEq("property"))).WillOnce(Return(&propMock2));

    EXPECT_CALL(propMock2, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(1).first.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(propMock2, QueryStringAttribute(StrEq("value"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.properties_.at(1).second.c_str()), Return(XML_SUCCESS)));

    EXPECT_CALL(propMock2, NextSiblingElement(StrEq("property"))).WillOnce(Return(nullptr));
}

void ParseHelperTest::ExpectParseImage(XMLElementMock *mock, const ParsedImage &expected) const
{
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

TEST_F(ParseHelperTest, ParseMapShouldSucceed)
{
    ParsedMap expected{"order", 1000, 1000, 10, 10};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("renderorder"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.renderOrder_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("width"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("height"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.height_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileHeight_), Return(XML_SUCCESS)));

    ParsedMap map;
    auto result = helper_.ParseMap(&mock, map);
    auto matcher = UnorderedElementsAre(
        ParseResult{"renderorder", XMLErrorMock::XML_SUCCESS}, ParseResult{"width", XMLErrorMock::XML_SUCCESS},
        ParseResult{"height", XMLErrorMock::XML_SUCCESS}, ParseResult{"tilewidth", XMLErrorMock::XML_SUCCESS},
        ParseResult{"tileheight", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(map, Eq(expected));
}

TEST_F(ParseHelperTest, ParseTmxTileSetShouldSucceed)
{
    ParsedTmxTileSet expected{100, "source"};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryAttribute(StrEq("firstgid"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.firstGid_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryStringAttribute(StrEq("source"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tsxSource_.c_str()), Return(XML_SUCCESS)));

    ParsedTmxTileSet tileSet;
    auto result = helper_.ParseTmxTileSet(&mock, tileSet);
    auto matcher = UnorderedElementsAre(ParseResult{"firstgid", XMLErrorMock::XML_SUCCESS},
                                        ParseResult{"source", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(tileSet, Eq(expected));
}

TEST_F(ParseHelperTest, ParseLayerShouldSucceed)
{
    ParsedLayer expected{1122, "name", 100, 100, "data"};
    XMLElementMock mock;
    XMLElementMock dataMock;

    EXPECT_CALL(mock, QueryAttribute(StrEq("id"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.name_.c_str()), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("width"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.width_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("height"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.height_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, FirstChildElement(StrEq("data"))).WillOnce(Return(&dataMock));
    EXPECT_CALL(dataMock, GetText()).WillOnce(Return(expected.data_.c_str()));

    ParsedLayer layer;
    auto result = helper_.ParseLayer(&mock, layer);
    auto matcher = UnorderedElementsAre(
        ParseResult{"id", XMLErrorMock::XML_SUCCESS}, ParseResult{"name", XMLErrorMock::XML_SUCCESS},
        ParseResult{"width", XMLErrorMock::XML_SUCCESS}, ParseResult{"height", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(layer, Eq(expected));
}

TEST_F(ParseHelperTest, ParseObjectGroupShouldSucceed)
{
    ParsedObjectGroup expected{1122,
                               "name",
                               {{1, "enemy1", 120, 120, 0, 0, {{"prop1", "value1"}, {"prop2", "value2"}}},
                                {2, "enemy2", 220, 220, 0, 0, {{"prop1", "value1"}, {"prop2", "value2"}}},
                                {3, "enemy3", 1120, 1120, 0, 0, {{"prop1", "value1"}, {"prop2", "value2"}}},
                                {4, "rect", 10, 11, 300, 200, {{"prop1", "value1"}, {"prop2", "value2"}}}}};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryAttribute(StrEq("id"), An<int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char **>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.name_.c_str()), Return(XML_SUCCESS)));

    XMLElementMock objectMock1;
    XMLElementMock propertiesMock1;
    std::vector<XMLElementMock> propMocks1(2);
    EXPECT_CALL(mock, FirstChildElement(StrEq("object"))).WillOnce(Return(&objectMock1));
    ExpectParseObject(&objectMock1, &propertiesMock1, propMocks1, expected.objects_.at(0));

    XMLElementMock objectMock2;
    XMLElementMock propertiesMock2;
    std::vector<XMLElementMock> propMocks2(2);
    EXPECT_CALL(objectMock1, NextSiblingElement(StrEq("object"))).WillOnce(Return(&objectMock2));
    ExpectParseObject(&objectMock2, &propertiesMock2, propMocks2, expected.objects_.at(1));

    XMLElementMock objectMock3;
    XMLElementMock propertiesMock3;
    std::vector<XMLElementMock> propMocks3(2);
    EXPECT_CALL(objectMock2, NextSiblingElement(StrEq("object"))).WillOnce(Return(&objectMock3));
    ExpectParseObject(&objectMock3, &propertiesMock3, propMocks3, expected.objects_.at(2));

    XMLElementMock objectMock4;
    XMLElementMock propertiesMock4;
    std::vector<XMLElementMock> propMocks4(2);
    EXPECT_CALL(objectMock3, NextSiblingElement(StrEq("object"))).WillOnce(Return(&objectMock4));
    ExpectParseRectObject(&objectMock4, &propertiesMock4, propMocks4, expected.objects_.at(3));

    EXPECT_CALL(objectMock4, NextSiblingElement(StrEq("object"))).WillOnce(Return(nullptr));

    ParsedObjectGroup group;
    auto result = helper_.ParseObjectGroup(&mock, group);
    auto matcher = UnorderedElementsAre(
        ParseResult{"id", XMLErrorMock::XML_SUCCESS}, ParseResult{"name", XMLErrorMock::XML_SUCCESS},
        ParseResult{"id", XMLErrorMock::XML_SUCCESS}, ParseResult{"type", XMLErrorMock::XML_SUCCESS},
        ParseResult{"x", XMLErrorMock::XML_SUCCESS}, ParseResult{"y", XMLErrorMock::XML_SUCCESS},
        ParseResult{"width", XMLErrorMock::XML_SUCCESS}, ParseResult{"height", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS},
        ParseResult{"id", XMLErrorMock::XML_SUCCESS}, ParseResult{"type", XMLErrorMock::XML_SUCCESS},
        ParseResult{"x", XMLErrorMock::XML_SUCCESS}, ParseResult{"y", XMLErrorMock::XML_SUCCESS},
        ParseResult{"width", XMLErrorMock::XML_SUCCESS}, ParseResult{"height", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS},
        ParseResult{"id", XMLErrorMock::XML_SUCCESS}, ParseResult{"type", XMLErrorMock::XML_SUCCESS},
        ParseResult{"x", XMLErrorMock::XML_SUCCESS}, ParseResult{"y", XMLErrorMock::XML_SUCCESS},
        ParseResult{"width", XMLErrorMock::XML_SUCCESS}, ParseResult{"height", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS},
        ParseResult{"id", XMLErrorMock::XML_SUCCESS}, ParseResult{"type", XMLErrorMock::XML_SUCCESS},
        ParseResult{"x", XMLErrorMock::XML_SUCCESS}, ParseResult{"y", XMLErrorMock::XML_SUCCESS},
        ParseResult{"width", XMLErrorMock::XML_SUCCESS}, ParseResult{"height", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS},
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"value", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(group, Eq(expected));
}

TEST_F(ParseHelperTest, ParseTileSetShouldSucceed)
{
    ParsedTileSet expected{"tsname", 16, 80, 3, 0};
    XMLElementMock mock;

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

    ParsedTileSet tileSet;
    auto result = helper_.ParseTileSet(&mock, tileSet);
    auto matcher = UnorderedElementsAre(
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"tilewidth", XMLErrorMock::XML_SUCCESS},
        ParseResult{"tileheight", XMLErrorMock::XML_SUCCESS}, ParseResult{"tilecount", XMLErrorMock::XML_SUCCESS},
        ParseResult{"columns", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(tileSet, Eq(expected));
}

TEST_F(ParseHelperTest, ParseTileSetShouldFailDueToWrongAttributeName)
{
    ParsedTileSet expected{"tsname", 16, {}, 3, 0};
    XMLElementMock mock;

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

    ParsedTileSet tileSet;
    auto result = helper_.ParseTileSet(&mock, tileSet);
    auto matcher = UnorderedElementsAre(
        ParseResult{"name", XMLErrorMock::XML_SUCCESS}, ParseResult{"tilewidth", XMLErrorMock::XML_SUCCESS},
        ParseResult{"tileheight", XMLErrorMock::XML_WRONG_ATTRIBUTE_TYPE},
        ParseResult{"tilecount", XMLErrorMock::XML_SUCCESS}, ParseResult{"columns", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(tileSet, Eq(expected));
}

TEST_F(ParseHelperTest, ParseTileSetShouldFailDueToNoAttribute)
{
    ParsedTileSet expected{{}, 16, 0, 3, 0};
    XMLElementMock mock;

    EXPECT_CALL(mock, QueryStringAttribute(StrEq("name"), An<const char **>())).WillOnce(Return(XML_NO_ATTRIBUTE));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilewidth"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tileheight"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileHeight_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("tilecount"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, QueryAttribute(StrEq("columns"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.columns_), Return(XML_SUCCESS)));

    ParsedTileSet tileSet;
    auto result = helper_.ParseTileSet(&mock, tileSet);
    auto matcher = UnorderedElementsAre(
        ParseResult{"name", XMLErrorMock::XML_NO_ATTRIBUTE}, ParseResult{"tilewidth", XMLErrorMock::XML_SUCCESS},
        ParseResult{"tileheight", XMLErrorMock::XML_SUCCESS}, ParseResult{"tilecount", XMLErrorMock::XML_SUCCESS},
        ParseResult{"columns", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(tileSet, Eq(expected));
}

TEST_F(ParseHelperTest, ParseImageShouldSucceed)
{
    ParsedImage expected{"myImage.png", 16, 16};
    XMLElementMock mock;
    ExpectParseImage(&mock, expected);

    ParsedImage image;
    auto result = helper_.ParseImage(&mock, image);
    auto matcher = UnorderedElementsAre(ParseResult{"source", XMLErrorMock::XML_SUCCESS},
                                        ParseResult{"width", XMLErrorMock::XML_SUCCESS},
                                        ParseResult{"height", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(image, Eq(expected));
}

TEST_F(ParseHelperTest, ParseTileWithOnlyImageShouldSucceed)
{
    ParsedImage expectedImage{"myImage1.png", 16, 16};
    ParsedTile expected{110, expectedImage, {}};
    XMLElementMock mock;
    XMLElementMock imageMock;

    EXPECT_CALL(mock, QueryAttribute(StrEq("id"), An<unsigned int *>()))
        .WillOnce(DoAll(SetArgPointee<1>(expected.id_), Return(XML_SUCCESS)));
    EXPECT_CALL(mock, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageMock));
    ExpectParseImage(&imageMock, expectedImage);
    EXPECT_CALL(mock, FirstChildElement(StrEq("animation"))).WillOnce(Return(nullptr));

    ParsedTile tile;
    auto result = helper_.ParseTile(&mock, tile);
    auto matcher = UnorderedElementsAre(
        ParseResult{"id", XMLErrorMock::XML_SUCCESS}, ParseResult{"source", XMLErrorMock::XML_SUCCESS},
        ParseResult{"width", XMLErrorMock::XML_SUCCESS}, ParseResult{"height", XMLErrorMock::XML_SUCCESS});
    EXPECT_THAT(result, matcher);
    EXPECT_THAT(tile, Eq(expected));
}

}  // namespace Tile

}  // namespace FA
