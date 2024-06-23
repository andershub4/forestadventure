/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "Resource/TextureRect.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(TextureRectTest, DefaultConstructorGivesInvalidRect)
{
    TextureRect r;
    EXPECT_FALSE(r.isValid_);
}

TEST(TextureRectTest, ConstructorGivesValidRect)
{
    TextureRect r(343, {3, 3, 10, 10});
    EXPECT_TRUE(r.isValid_);
}

TEST(TextureRectTest, TestTextureRectEqualToOperator)
{
    TextureRect r1(343, {3, 3, 10, 10});
    TextureRect r2 = r1;
    EXPECT_TRUE(r1 == r2);
    r1.rect_.height = 5;
    EXPECT_FALSE(r1 == r2);
}

}  // namespace Shared

}  // namespace FA
