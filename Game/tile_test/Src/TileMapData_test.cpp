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

}  // namespace Tile

}  // namespace FA
