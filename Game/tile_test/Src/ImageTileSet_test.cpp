/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>

#include "ImageTileSet.h"

using namespace testing;

namespace FA {

namespace Tile {

class ImageTileSetTest : public Test
{
protected:
    const std::string dirStr_ = "dev/tsxDir";
    const ParsedImage image1_{"../myImage1.png", 16, 16};
    const ParsedImage image2_{"../myImage2.png", 16, 16};
    const ParsedAnimation animation_{{{110, 20}, {111, 20}}};
    const ParsedTile tile1_{110, image1_, animation_};
    const ParsedTile tile2_{111, image2_, {}};
    const ParsedTile tile3_{112, {}, {}};
    const ParsedTile tile4_{113, {}, {}};
};

TEST_F(ImageTileSetTest, NoTilesShouldReturnEmptySet)
{
    ImageTileSet imageTileSet{dirStr_, {}};
    auto tileSetData = imageTileSet.GenerateTileData();

    TileSetData expected{};

    EXPECT_EQ(expected, tileSetData);
}

TEST_F(ImageTileSetTest, TwoTilesWithImageAndAnimationShouldReturnTwoImagesAndTwoEntries)
{
    ImageTileSet imageTileSet{dirStr_, {tile1_, tile2_}};
    auto tileSetData = imageTileSet.GenerateTileData();

    Image i1("dev/myImage1.png");
    Image i2("dev/myImage2.png");
    std::vector<Image> expectedImages{i1, i2};
    Frame f1{"dev/myImage1.png", 0, 0, 16, 16};
    Frame f2{"dev/myImage2.png", 0, 0, 16, 16};
    std::unordered_map<int, TileData> expectedLookup{{110, TileData{f1, {f1, f2}}}, {111, TileData{f2, {}}}};

    TileSetData expected{expectedImages, expectedLookup};

    EXPECT_EQ(expected, tileSetData);
}

TEST_F(ImageTileSetTest, TwoTilesWithoutImageShouldReturnNoImageAndTwoEmptyEntries)
{
    ImageTileSet imageTileSet{dirStr_, {tile3_, tile4_}};
    auto tileSetData = imageTileSet.GenerateTileData();

    TileSetData expected{{}, {{112, {}}, {113, {}}}};

    EXPECT_EQ(expected, tileSetData);
}

}  // namespace Tile

}  // namespace FA
