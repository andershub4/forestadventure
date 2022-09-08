/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "TileMapData.h"

using namespace testing;

namespace FA {

namespace Tile {

TEST(TileMapDataTest, TestImageEqualToOperator)
{
    Image d1{"dev/dir", 10, 10};
    Image d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.nCols_ = 11;
    EXPECT_FALSE(d1 == d2);
}

TEST(TileMapDataTest, TestFrameEqualToOperator)
{
    Frame d1{"dev/dir", 3, 4, 16, 16};
    Frame d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.width_ = 32;
    d1.height_ = 32;
    EXPECT_FALSE(d1 == d2);
}

TEST(TileMapDataTest, TestFrameDataEqualToOperator)
{
    Frame d1{"dev/dir", 1, 4, 16, 16};
    Frame d2{"dev/dir", 2, 4, 16, 16};
    Frame d3{"dev/dir", 3, 4, 16, 16};

    FrameData f1{{}, {d1, d2}};
    FrameData f2 = f1;
    FrameData f3{{}, {d3}};

    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
}

TEST(TileMapDataTest, TestTileSetDataEqualToOperator)
{
    Image i1{"dev/dir", 10, 10};
    Frame f1{"dev/dir", 1, 4, 16, 16};
    Frame f2{"dev/dir", 2, 4, 16, 16};
    FrameData fd1{{}, {f1, f2}};
    TileSetData d1{{i1}, {{10, fd1}}};
    TileSetData d2 = d1;

    EXPECT_TRUE(d1 == d2);
    TileSetData d3{{i1}, {{11, fd1}}};
    EXPECT_FALSE(d1 == d3);
}

TEST(TileMapDataTest, TestMapPropertiesEqualToOperator)
{
    TileMapData::MapProperties d1{100, 100, 10, 10};
    auto d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d2.tileWidth_++;
    EXPECT_FALSE(d1 == d2);
}

TEST(TileMapDataTest, TestLayerEqualToOperator)
{
    TileMapData::Layer d1{"testLayer", {1, 2, 3, 4}};
    auto d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d2.name_ = "myLayer";
    EXPECT_FALSE(d1 == d2);
}

TEST(TileMapDataTest, TestObjectEqualToOperator)
{
    TileMapData::Object d1{"obj1", 12, 13, {{"speed", "4"}, {"money", "100"}}};
    auto d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d2.properties_ = {{"speed", "5"}, {"money", "0"}};
    EXPECT_FALSE(d1 == d2);
}

TEST(TileMapDataTest, TestObjectGroupEqualToOperator)
{
    TileMapData::Object obj1{"obj1", 12, 13, {{"speed", "4"}, {"money", "100"}}};
    TileMapData::Object obj2{"obj2", 12, 13, {{"speed", "40"}, {"money", "0"}}};
    TileMapData::ObjectGroup d1{"group1", {obj1, obj2}};
    auto d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d2.objects_.clear();
    EXPECT_FALSE(d1 == d2);
}

TEST(TileMapDataTest, TestTileMapDataEqualToOperator)
{
    Image i1{"dev/dir", 10, 10};
    Frame f1{"dev/dir", 1, 4, 16, 16};
    Frame f2{"dev/dir", 2, 4, 16, 16};
    FrameData fd1{{}, {f1, f2}};
    TileSetData tsd{{i1}, {{10, fd1}}};
    TileMapData::MapProperties mp{100, 100, 16, 16};
    std::map<int, TileSetData, std::greater<int>> tileSets{{0, tsd}};
    std::vector<TileMapData::Layer> layers{{"ObjLayer1", {1, 2, 34}}, {"ObjLayer2", {2, 3, 4, 5, 6, 7}}};
    TileMapData::Object obj1{"type1", 12, 33, {{"AiMoveAlgo", "AStar"}}};
    std::vector<TileMapData::ObjectGroup> objectGroups{{"group1", {obj1}}};

    TileMapData d1{mp, tileSets, layers, objectGroups};
    auto d2 = d1;
    EXPECT_TRUE(d1 == d2);

    d2.mapProperties_.height_++;
    EXPECT_FALSE(d1 == d2);
}

}  // namespace Tile

}  // namespace FA
