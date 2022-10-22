/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <vector>

#include <gtest/gtest.h>

#include "Mock/TileSetFactoryMock.h"
#include "Mock/TileSetMock.h"
#include "Mock/TmxParserMock.h"
#include "Mock/TsxParserMock.h"
#include "Mock/XMLMock.h"

#include "TileService.h"

using namespace testing;

namespace FA {

std::string GetFileBuffer(const std::string &fileName)
{
    return "buffer";
}

namespace Tile {

class TileServiceTest : public Test
{
protected:
    virtual void SetUp() override;

    const std::string tmxPath_ = "assets/map/test.tmx";
    const std::string tmxDir_ = "assets/map";

    const ParsedMap map_{"right-down", 100, 100, 16, 16};
    const ParsedTmxTileSet tmxTileSet_{12, "tileset.tsx"};
    const ParsedLayer layer1_{1, "Ground Layer 1", 100, 100, "849, 849, 850"};
    const ParsedLayer layer2_{1, "Ground Layer 2", 100, 100, "149, 149, 150"};
    const ParsedObject object1_{4, "Player", 360, 296, {{"FaceDirection", "Down"}}};
    const ParsedObject object2_{5, "Enemy", 260, 196, {{"FaceDirection", "Down"}}};
    const ParsedObjectGroup group_{2, "ObjectGroup1", {object1_, object2_}};

    TmxParserMock<XMLDocumentMock, XMLElementMock, XMLError> tmxParserMock_;
    TsxParserMock<XMLDocumentMock, XMLElementMock, XMLError> tsxParserMock_;
    TileSetFactoryMock tileSetFactoryMock_;

    std::unique_ptr<TileService<XMLDocumentMock, XMLElementMock, XMLError>> service_;
};

void TileServiceTest::SetUp()
{
    auto tmxParserMockProxy =
        std::make_unique<TmxParserMockProxy<XMLDocumentMock, XMLElementMock, XMLError>>(tmxParserMock_);
    auto tsxParserMockProxy =
        std::make_unique<TsxParserMockProxy<XMLDocumentMock, XMLElementMock, XMLError>>(tsxParserMock_);
    auto tileSetFactoryMockProxy = std::make_unique<TileSetFactoryMockProxy>(tileSetFactoryMock_);
    service_ = std::make_unique<TileService<XMLDocumentMock, XMLElementMock, XMLError>>(
        std::move(tmxParserMockProxy), std::move(tsxParserMockProxy), std::move(tileSetFactoryMockProxy));
}

TEST_F(TileServiceTest, ReadMapPropertiesShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_}, {group_}};
    EXPECT_CALL(tmxParserMock_, Parse(_, _, _)).WillOnce(DoAll(SetArgReferee<2>(parsedTmx), Return(true)));

    EXPECT_TRUE(service_->Parse(tmxPath_));

    auto mapProperties = service_->ReadMapProperties();
    TileMapData::MapProperties expectedMapProperties{100, 100, 16, 16};
    EXPECT_THAT(mapProperties, Eq(expectedMapProperties));
}

TEST_F(TileServiceTest, ReadTileSetsShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_}, {group_}};
    EXPECT_CALL(tmxParserMock_, Parse(_, _, _)).WillOnce(DoAll(SetArgReferee<2>(parsedTmx), Return(true)));

    EXPECT_TRUE(service_->Parse(tmxPath_));

    ParsedTsx parsedTsx;
    Image image1("assets/animation/spinning1.png");
    Image image2("assets/animation/spinning2.png");
    Image image3("assets/animation/spinning3.png");
    Frame frame1{"assets/animation/spinning1.png", 0, 0, 32, 80};
    Frame frame2{"assets/animation/spinning2.png", 0, 0, 32, 80};
    Frame frame3{"assets/animation/spinning3.png", 0, 0, 32, 80};
    FrameData frameData1{frame1, {frame1, frame2, frame3}};
    FrameData frameData2{frame2, {}};
    FrameData frameData3{frame3, {}};
    TileSetData imageTileSetData{{image1, image2, image3}, {{0, frameData1}, {1, frameData2}, {2, frameData3}}};
    auto tileSetMock = std::make_unique<TileSetMock>();
    EXPECT_CALL(tsxParserMock_, Parse(_, _, _)).WillOnce(DoAll(SetArgReferee<2>(parsedTsx), Return(true)));
    EXPECT_CALL(*tileSetMock, GenerateTileData()).WillOnce(Return(imageTileSetData));
    EXPECT_CALL(tileSetFactoryMock_, Create(_, _, _, _)).WillOnce(Return(ByMove(std::move(tileSetMock))));

    auto tileSets = service_->ReadTileSets(tmxDir_);
    std::map<int, TileSetData, std::greater<int>> expectedTileSets{{12, imageTileSetData}};
    EXPECT_THAT(tileSets, Eq(expectedTileSets));
}

TEST_F(TileServiceTest, ReadLayersShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_, layer2_}, {group_}};
    EXPECT_CALL(tmxParserMock_, Parse(_, _, _)).WillOnce(DoAll(SetArgReferee<2>(parsedTmx), Return(true)));

    EXPECT_TRUE(service_->Parse(tmxPath_));

    auto layers = service_->ReadLayers();
    std::vector<TileMapData::Layer> expectedLayers{{"Ground Layer 1", {849, 849, 850}},
                                                   {"Ground Layer 2", {149, 149, 150}}};
    EXPECT_THAT(layers, Eq(expectedLayers));
}

TEST_F(TileServiceTest, ReadObjectGroupsShouldSucceed)
{
    ParsedTmx parsedTmx{map_, {tmxTileSet_}, {layer1_}, {group_}};
    EXPECT_CALL(tmxParserMock_, Parse(_, _, _)).WillOnce(DoAll(SetArgReferee<2>(parsedTmx), Return(true)));

    EXPECT_TRUE(service_->Parse(tmxPath_));

    auto objectGroups = service_->ReadObjectGroups();
    std::vector<TileMapData::ObjectGroup> expectedObjectGroups{
        {"ObjectGroup1",
         {{"Player", 360, 296, {{"FaceDirection", "Down"}}}, {"Enemy", 260, 196, {{"FaceDirection", "Down"}}}}}};
    EXPECT_THAT(objectGroups, Eq(expectedObjectGroups));
}

}  // namespace Tile

}  // namespace FA
