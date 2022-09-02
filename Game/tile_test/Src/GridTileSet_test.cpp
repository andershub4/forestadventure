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
    const GridTileSet::Dimensions dim100Tiles_{16, 16, 20, 100};
};

TEST_F(GridTileSetTest, TileSetShouldReturnSingleImage)
{
    GridTileSet imageTileSet{dirStr_, path_, dim100Tiles_};
    auto images = imageTileSet.GetImages();

    std::vector<Image> expected{{"dev/myImage1.png", 20, 5}};
    EXPECT_EQ(expected, images);
}

TEST_F(GridTileSetTest, TileSetShouldReturnOneFramePerTile)
{
    GridTileSet imageTileSet{dirStr_, path_, dim100Tiles_};
    auto frameDatas = imageTileSet.GetFrameDatas();

    EXPECT_EQ(100, frameDatas.size());

    auto firstFrameData = frameDatas[0];
    Frame firstExpectedFrame{"dev/myImage1.png", 0, 0, 16, 16};
    std::vector<Frame> firstExpectedVec{firstExpectedFrame};
    FrameData firstExpected(firstExpectedVec);
    EXPECT_EQ(firstExpected, firstFrameData);

    auto lastFrameData = frameDatas[99];
    Frame lastExpectedFrame{"dev/myImage1.png", 19, 4, 16, 16};
    std::vector<Frame> lastExpectedVec{lastExpectedFrame};
    FrameData lastExpected(lastExpectedVec);
    EXPECT_EQ(lastExpected, lastFrameData);
}

}  // namespace Tile

}  // namespace FA
