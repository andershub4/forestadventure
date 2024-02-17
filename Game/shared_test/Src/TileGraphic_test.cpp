/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>
#include "Resource/TileGraphic.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(TileGraphicTest, TestTileGraphicEqualToOperator)
{
    ImageData idata{"mySheet1", {12, 10}};
    ImageData adata1{"mySheet2", {0, 0}};
    ImageData adata2{"mySheet2", {10, 0}};
    TileGraphic t1{{adata1, adata2}, idata};
    TileGraphic t2 = t1;
    EXPECT_TRUE(t1 == t2);
    ImageData adata3{"mySheet2", {20, 0}};
    t1.animation_.push_back(adata3);
    EXPECT_FALSE(t1 == t2);
}

}  // namespace Shared

}  // namespace FA
