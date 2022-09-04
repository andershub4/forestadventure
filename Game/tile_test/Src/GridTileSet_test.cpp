/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <unordered_map>
#include <vector>

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
    const GridTileSet::Dimensions dimFourTiles_{16, 16, 2, 4};
};

TEST_F(GridTileSetTest, TileSetShouldCreateFourEntries)
{
    GridTileSet imageTileSet{dirStr_, path_, dimFourTiles_};
    auto tileSetData = imageTileSet.CreateTileSetData();

    std::vector<Image> expectedImage{{"dev/myImage1.png", 2, 2}};
    Frame expectedFrame1{"dev/myImage1.png", 0, 0, 16, 16};
    Frame expectedFrame2{"dev/myImage1.png", 1, 0, 16, 16};
    Frame expectedFrame3{"dev/myImage1.png", 0, 1, 16, 16};
    Frame expectedFrame4{"dev/myImage1.png", 1, 1, 16, 16};
    std::unordered_map<int, FrameData> expectedLookupTable{{0, FrameData{expectedFrame1, {}}},
                                                           {1, FrameData{expectedFrame2, {}}},
                                                           {2, FrameData{expectedFrame3, {}}},
                                                           {3, FrameData{expectedFrame4, {}}}};
    TileSetData expected{expectedImage, expectedLookupTable};

    EXPECT_EQ(expected, tileSetData);
}

}  // namespace Tile

}  // namespace FA
