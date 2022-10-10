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
#include "ImageTileSet.h"
#include "TileSetFactory.h"

using namespace testing;

namespace FA {

namespace Tile {

class TileSetFactoryTest : public Test
{
protected:
    const std::string dirStr_{"dev/tsxDir"};
    const std::string imageSrc_{"../test.png"};
    const ParsedImage image1_{"../myImage1.png", 16, 16};
    const ParsedImage image2_{"../myImage2.png", 16, 16};
    const ParsedAnimation animation_{{{110, 20}, {111, 20}}};
    const ParsedTile tile1_{110, image1_, animation_};
    const ParsedTile tile2_{111, image2_, {}};
    const ParsedTileSet tileSet_{"name", 16, 16, 4, 2};

    TileSetFactory factory_;
};

TEST_F(TileSetFactoryTest, TileSetFactoryShouldCreateImageTileSet)
{
    std::vector<ParsedTile> tiles{tile1_, tile2_};
    auto set = factory_.Create(dirStr_, tiles, tileSet_, imageSrc_);
    ASSERT_THAT(set, NotNull());
    auto ptr = dynamic_cast<ImageTileSet*>(set.get());
    EXPECT_THAT(ptr, NotNull());
}

TEST_F(TileSetFactoryTest, TileSetFactoryShouldCreateGridTileSet)
{
    std::vector<ParsedTile> tiles;
    auto set = factory_.Create(dirStr_, tiles, tileSet_, imageSrc_);
    ASSERT_THAT(set, NotNull());
    auto ptr = dynamic_cast<GridTileSet*>(set.get());
    EXPECT_THAT(ptr, NotNull());
}

}  // namespace Tile

}  // namespace FA
