/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>
#include "Resource/SheetItem.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(SheetItemTest, TestSheetItemEqualToOperator)
{
    SheetItem item1{"mysheet1", {20, 0}};
    SheetItem item2 = item1;
    EXPECT_TRUE(item1 == item2);
    item1.sheetId_ = "mysheet32";
    EXPECT_FALSE(item1 == item2);
}

}  // namespace Shared

}  // namespace FA
