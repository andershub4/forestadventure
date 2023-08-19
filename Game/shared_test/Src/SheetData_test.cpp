/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "Resource/SheetData.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(SheetDataTest, TestSheetDataEqualToOperator)
{
    SheetData d1{"myname", "/mypath/mydata.jpg", {0, 0}};
    SheetData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.rectCount_ = sf::Vector2u(2, 2);
    EXPECT_FALSE(d1 == d2);
}

}  // namespace Shared

}  // namespace FA
