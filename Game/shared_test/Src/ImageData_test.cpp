/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "Resource/ImageData.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(ImageDataTest, TestImageDataEqualToOperator)
{
    ImageData d1{"sheet1", {0, 0}};
    ImageData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.sheetId_ = "mysheet";
    EXPECT_FALSE(d1 == d2);
}

}  // namespace Shared

}  // namespace FA
