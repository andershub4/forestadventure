/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Resource/ColliderData.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(ColliderDataTest, TestColliderDataEqualToOperator)
{
    ColliderData d1{{"sheet1", {0, 0}}};
    ColliderData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.sheetItem_.id_ = "mysheet";
    EXPECT_FALSE(d1 == d2);
}

}  // namespace Shared

}  // namespace FA
