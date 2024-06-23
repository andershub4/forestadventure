/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "Resource/Frame.h"
#include "TextureIf.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(FrameTest, TestFrameEqualToOperator)
{
    sf::IntRect rect{12, 12, 10, 10};
    Graphic::TextureIf* texture = nullptr;
    Frame d1{texture, rect};
    Frame d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.rect_.left = 399;
    EXPECT_FALSE(d1 == d2);
}

}  // namespace Shared

}  // namespace FA
