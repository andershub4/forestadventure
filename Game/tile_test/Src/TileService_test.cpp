/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <vector>

#include <gtest/gtest.h>

#include "Mock/ByteStreamFactoryMock.h"
#include "Mock/ByteStreamMock.h"
#include "Mock/TileSetFactoryMock.h"
#include "Mock/TileSetMock.h"
#include "Mock/TmxLoggerMock.h"
#include "Mock/TmxParserMock.h"
#include "Mock/TsxParserMock.h"
#include "Mock/XMLMock.h"

#include "TileService.h"

using namespace testing;

namespace FA {

namespace Tile {

class TileServiceTest : public Test
{
protected:
    virtual void SetUp() override;

    const std::string tmxPath_ = "assets/map/test.tmx";
    const std::string tmxDir_ = "assets/map";
    const std::string tsxDir_ = "assets/map";

    const ParsedMap map_{"right-down", 100, 100, 16, 16};
    const ParsedTmxTileSet tmxTileSet_{12, "tileset.tsx"};
    const ParsedLayer layer1_{1, "Ground Layer 1", 100, 100, "849, 849, 850"};
    const ParsedLayer layer2_{1, "Ground Layer 2", 100, 100, "149, 149, 150"};
    const ParsedObject object1_{4, "Player", 360, 296, 0, 0, {{"FaceDirection", "Down"}}};
    const ParsedObject object2_{5, "Enemy", 260, 196, 0, 0, {{"FaceDirection", "Down"}}};
    const ParsedObject object3_{5, "Rect", 260, 196, 20, 10, {{"Solid", "1"}}};
    const ParsedObjectGroup group_{2, "ObjectGroup1", {object1_, object2_, object3_}};

    const ParsedTileSet tileSet_{"tsname", 16, 80, 3, 0};
    const ParsedImage image_{"myImage1.png", 16, 16};
    const ParsedAnimation animation1_{{{0, 20}, {1, 20}, {1, 20}}};
    const ParsedAnimation animation2_{{{0, 20}, {1, 20}, {1, 20}}};
    const ParsedAnimation animation3_{{}};
    const ParsedTile tile1_{110, image_, animation1_};
    const ParsedTile tile2_{111, image_, animation2_};
    const ParsedTile tile3_{111, image_, animation3_};
    const std::vector<ParsedTile> parsedTiles_{tile1_, tile2_, tile3_};

    Image image1{"assets/animation/spinning1.png"};
    Image image2{"assets/animation/spinning2.png"};
    Image image3{"assets/animation/spinning3.png"};
    Frame frame1{"assets/animation/spinning1.png", 0, 0, 32, 80};
    Frame frame2{"assets/animation/spinning2.png", 0, 0, 32, 80};
    Frame frame3{"assets/animation/spinning3.png", 0, 0, 32, 80};
    TileData tileData1{frame1, {frame1, frame2, frame3}};
    TileData tileData2{frame2, {}};
    TileData tileData3{frame3, {}};
    TileSetData imageTileSetData_{{image1, image2, image3}, {{0, tileData1}, {1, tileData2}, {2, tileData3}}};

    StrictMock<TmxParserMock> tmxParserMock_;
    StrictMock<TsxParserMock> tsxParserMock_;
    StrictMock<TileSetFactoryMock> tileSetFactoryMock_;
    StrictMock<Util::ByteStreamFactoryMock> byteStreamFactoryMock_;
    StrictMock<LoggerMock> loggerMock_;

    std::unique_ptr<TileService<XMLDocumentMock, XMLElementMock, XMLErrorMock>> service_;

protected:
    void ExpectParseSucceed(const ParsedTmx &parsedTmx);
};

void TileServiceTest::SetUp()
{
    auto tmxParserMockProxy = std::make_unique<TmxParserMockProxy>(tmxParserMock_);
    auto tsxParserMockProxy = std::make_unique<TsxParserMockProxy>(tsxParserMock_);
    auto tileSetFactoryMockProxy = std::make_unique<TileSetFactoryMockProxy>(tileSetFactoryMock_);
    auto byteStreamFactoryMockProxy = std::make_unique<Util::ByteStreamFactoryMockProxy>(byteStreamFactoryMock_);
    service_ = std::make_unique<TileService<XMLDocumentMock, XMLElementMock, XMLErrorMock>>(
        std::move(tmxParserMockProxy), std::move(tsxParserMockProxy), std::move(tileSetFactoryMockProxy),
        std::move(byteStreamFactoryMockProxy));
}

void TileServiceTest::ExpectParseSucceed(const ParsedTmx &parsedTmx)
{
    auto byteStreamMock = std::make_unique<Util::ByteStreamMock>();
    EXPECT_CALL(*byteStreamMock, GetBuffer()).WillOnce(Return("xmlbuffer"));
    EXPECT_CALL(byteStreamFactoryMock_, Create(tmxPath_)).WillOnce(Return(ByMove(std::move(byteStreamMock))));
    EXPECT_CALL(tmxParserMock_, Parse(_, StrEq("xmlbuffer"), _))
        .WillOnce(DoAll(SetArgReferee<2>(parsedTmx), Return(true)));

    EXPECT_TRUE(service_->Parse(tmxPath_));
}

TEST_F(TileServiceTest, ReadMapPropertiesShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_, layer2_}, {group_}};
    ExpectParseSucceed(parsedTmx);

    auto mapProperties = service_->ReadMapProperties();
    TileMapData::MapProperties expectedMapProperties{map_.width_, map_.height_, map_.tileWidth_, map_.tileHeight_};
    EXPECT_THAT(mapProperties, Eq(expectedMapProperties));
}

TEST_F(TileServiceTest, ReadTileSetsShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_, layer2_}, {group_}};
    ExpectParseSucceed(parsedTmx);

    ParsedTsx parsedTsx{tileSet_, image_, parsedTiles_};
    auto byteStreamMock = std::make_unique<Util::ByteStreamMock>();
    EXPECT_CALL(*byteStreamMock, GetBuffer()).WillOnce(Return("xmlbufferTsx"));
    auto tsxPath = tsxDir_ + "/" + tmxTileSet_.tsxSource_;
    EXPECT_CALL(byteStreamFactoryMock_, Create(StrEq(tsxPath))).WillOnce(Return(ByMove(std::move(byteStreamMock))));

    auto tileSetMock = std::make_unique<TileSetMock>();
    EXPECT_CALL(tsxParserMock_, Parse(_, StrEq("xmlbufferTsx"), _))
        .WillOnce(DoAll(SetArgReferee<2>(parsedTsx), Return(true)));
    EXPECT_CALL(*tileSetMock, GenerateTileData()).WillOnce(Return(imageTileSetData_));
    EXPECT_CALL(tileSetFactoryMock_, Create(StrEq(tsxDir_), parsedTiles_, tileSet_, image_.source_))
        .WillOnce(Return(ByMove(std::move(tileSetMock))));

    auto tileSets = service_->ReadTileSets(tmxDir_);
    std::map<int, TileSetData, std::greater<int>> expectedTileSets{{tmxTileSet_.firstGid_, imageTileSetData_}};
    EXPECT_THAT(tileSets, Eq(expectedTileSets));
}

TEST_F(TileServiceTest, ReadTileSetsShouldFailDueToNoTileSets)
{
    ParsedTmx parsedTmx{map_, {}, {layer1_, layer2_}, {group_}};
    ExpectParseSucceed(parsedTmx);

    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("No tilesets found")));

    auto tileSets = service_->ReadTileSets(tmxDir_);
    EXPECT_THAT(tileSets, IsEmpty());
}

TEST_F(TileServiceTest, ReadTileSetsShouldFailDueToUnableToParseTileSet)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_, layer2_}, {group_}};
    ExpectParseSucceed(parsedTmx);

    auto byteStreamMock = std::make_unique<Util::ByteStreamMock>();
    EXPECT_CALL(*byteStreamMock, GetBuffer()).WillOnce(Return("xmlbufferTsx"));
    auto tsxPath = tsxDir_ + "/" + tmxTileSet_.tsxSource_;
    EXPECT_CALL(byteStreamFactoryMock_, Create(StrEq(tsxPath))).WillOnce(Return(ByMove(std::move(byteStreamMock))));

    EXPECT_CALL(tsxParserMock_, Parse(_, StrEq("xmlbufferTsx"), _)).WillOnce(Return(false));
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("Can not parse: tileset.tsx")));

    auto tileSets = service_->ReadTileSets(tmxDir_);
    EXPECT_THAT(tileSets, IsEmpty());
}

TEST_F(TileServiceTest, ReadLayersShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_, layer2_}, {group_}};
    ExpectParseSucceed(parsedTmx);

    auto layers = service_->ReadLayers();
    std::vector<TileMapData::Layer> expectedLayers{{layer1_.name_, {849, 849, 850}}, {layer2_.name_, {149, 149, 150}}};
    EXPECT_THAT(layers, Eq(expectedLayers));
}

TEST_F(TileServiceTest, ReadObjectGroupsShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_, layer2_}, {group_}};
    ExpectParseSucceed(parsedTmx);

    auto objectGroups = service_->ReadObjectGroups();
    std::vector<TileMapData::ObjectGroup> expectedObjectGroups{
        {"ObjectGroup1",
         {{"Player", 360, 296, 0, 0, {{"FaceDirection", "Down"}}},
          {"Enemy", 260, 196, 0, 0, {{"FaceDirection", "Down"}}},
          {"Rect", 260, 196, 20, 10, {{"Solid", "1"}}}}}};
    EXPECT_THAT(objectGroups, Eq(expectedObjectGroups));
}

}  // namespace Tile

}  // namespace FA
