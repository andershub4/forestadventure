/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <unordered_map>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "GridTileSet.h"

using namespace testing;

namespace FA {

namespace Tile {

class GridTileSetTest : public Test
{
protected:
    const std::string dirStr_ = "dev/tsxDir";
    const std::string path_ = "../myImage1.png";
};

TEST_F(GridTileSetTest, EmptyTileSetShouldCreateNoEntries)
{
    const ParsedTileSet tileSet;
    GridTileSet gridTileSet{dirStr_, path_, tileSet};
    auto tileSetData = gridTileSet.GenerateTileData();

    EXPECT_THAT(tileSetData.lookupTable_, SizeIs(0));
}

TEST_F(GridTileSetTest, TileSetWithNoTilesShouldCreateNoEntries)
{
    const ParsedTileSet tileSet{"name", 16, 16, 0, 2};
    GridTileSet gridTileSet{dirStr_, path_, tileSet};
    auto tileSetData = gridTileSet.GenerateTileData();

    EXPECT_THAT(tileSetData.lookupTable_, SizeIs(0));
}

TEST_F(GridTileSetTest, TileSetWithTooManyTilesShouldCreateNoEntries)
{
    const ParsedTileSet tileSet{"name", 16, 16, 10000, 10};
    GridTileSet gridTileSet{dirStr_, path_, tileSet};
    auto tileSetData = gridTileSet.GenerateTileData();

    EXPECT_THAT(tileSetData.lookupTable_, SizeIs(0));
}

TEST_F(GridTileSetTest, TileSetWith4TilesShouldCreate4Entries)
{
    const ParsedTileSet tileSet{"name", 16, 16, 4, 2};
    GridTileSet gridTileSet{dirStr_, path_, tileSet};
    auto tileSetData = gridTileSet.GenerateTileData();

    std::vector<Image> expectedImage{{"dev/myImage1.png", 2, 2}};
    Frame expectedFrame1{"dev/myImage1.png", 0, 0, 16, 16};
    Frame expectedFrame2{"dev/myImage1.png", 1, 0, 16, 16};
    Frame expectedFrame3{"dev/myImage1.png", 0, 1, 16, 16};
    Frame expectedFrame4{"dev/myImage1.png", 1, 1, 16, 16};
    std::unordered_map<int, TileData> expectedLookupTable{{0, TileData{expectedFrame1, {}}},
                                                          {1, TileData{expectedFrame2, {}}},
                                                          {2, TileData{expectedFrame3, {}}},
                                                          {3, TileData{expectedFrame4, {}}}};
    TileSetData expected{expectedImage, expectedLookupTable};

    EXPECT_EQ(expected, tileSetData);
}

TEST_F(GridTileSetTest, TileSetWith100TilesShouldCreate100Entries)
{
    const ParsedTileSet tileSet{"name", 16, 16, 100, 10};
    GridTileSet gridTileSet{dirStr_, path_, tileSet};
    auto tileSetData = gridTileSet.GenerateTileData();

    EXPECT_THAT(tileSetData.lookupTable_, SizeIs(100));
}

}  // namespace Tile

}  // namespace FA
