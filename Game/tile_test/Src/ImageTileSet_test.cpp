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

TEST_F(ImageTileSetTest, NoTilesShouldReturnNoImages)
{
    ImageTileSet imageTileSet{dirStr_, {}};
    auto images = imageTileSet.GetImages();

    EXPECT_TRUE(images.empty());
}

TEST_F(ImageTileSetTest, TwoTilesWithImageShouldReturnTwoImages)
{
    ImageTileSet imageTileSet{dirStr_, {tile1_, tile2_}};
    auto images = imageTileSet.GetImages();
    Image i1("dev/myImage1.png");
    Image i2("dev/myImage2.png");
    std::vector<Image> expected{i1, i2};

    EXPECT_EQ(expected, images);
}

TEST_F(ImageTileSetTest, TwoTilesWithoutImageShouldReturnNoImages)
{
    ImageTileSet imageTileSet{dirStr_, {tile3_, tile4_}};
    auto images = imageTileSet.GetImages();

    EXPECT_TRUE(images.empty());
}

TEST_F(ImageTileSetTest, TileWithTwoAnimationFramesShouldReturnTwoFrames)
{
    ImageTileSet imageTileSet{dirStr_, {tile1_, tile2_}};
    auto frameDatas = imageTileSet.GetFrameDatas();
    Frame f1{"dev/myImage1.png", 0, 0, 16, 16};
    Frame f2{"dev/myImage2.png", 0, 0, 16, 16};
    std::unordered_map<int, FrameData> expected{{110, FrameData({f1, f2})}};

    EXPECT_EQ(expected, frameDatas);
}

}  // namespace Tile

}  // namespace FA
