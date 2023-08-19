/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "Resource/AnimationData.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(AnimationDataTest, TestAnimationDataEqualToOperator)
{
    AnimationData d1{"sheet1", {{0, 0}, 3, 0}, true};
    AnimationData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.sheetId_ = "mysheet";
    EXPECT_FALSE(d1 == d2);
}

TEST(AnimationDataTest, TestLocationDataEqualToOperator)
{
    AnimationData::LocationData d1{{0, 0}, 3, 0};
    AnimationData::LocationData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.defaultIndex_ = 555;
    EXPECT_FALSE(d1 == d2);
}

}  // namespace Shared

}  // namespace FA
