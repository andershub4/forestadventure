/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "ParsedElements.h"

using namespace testing;

namespace FA {

namespace Tile {

TEST(ParsedElementsTest, TestParsedTileSetDataEqualToOperator)
{
    ParsedTileSetData d1{"tsname", 16, 80, 3, 0};
    ParsedTileSetData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.name_ = "myname";
    EXPECT_FALSE(d1 == d2);
}

TEST(ParsedElementsTest, TestParsedImageEqualToOperator)
{
    ParsedImage d1{"myImage.png", 16, 16};
    ParsedImage d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.source_ = "myOtherImage.png";
    EXPECT_FALSE(d1 == d2);
}

TEST(ParsedElementsTest, TestParsedFrameEqualToOperator)
{
    ParsedFrame d1{0, 10};
    ParsedFrame d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.duration_ = 30;
    EXPECT_FALSE(d1 == d2);
}

TEST(ParsedElementsTest, TestParsedAnimationEqualToOperator)
{
    ParsedAnimation d1{{{0, 10}, {1, 10}, {2, 10}}};
    ParsedAnimation d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.frames_.erase(d1.frames_.begin() + 1);
    EXPECT_FALSE(d1 == d2);
}

TEST(ParsedElementsTest, TestParsedTileEqualToOperator)
{
    ParsedImage i{"myImage1.png", 16, 16};
    ParsedAnimation a1{{{0, 20}, {1, 20}, {1, 20}}};
    ParsedTile d1{110, i, a1};
    ParsedTile d2 = d1;
    EXPECT_TRUE(d1 == d2);
    ParsedAnimation a2{{{1, 20}, {1, 20}, {1, 20}}};
    d1.animation_ = a2;
    EXPECT_FALSE(d1 == d2);
}

}  // namespace Tile

}  // namespace FA
