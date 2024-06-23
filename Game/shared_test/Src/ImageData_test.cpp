/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Resource/ImageData.h"
#include "Resource/SheetItem.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(ImageDataTest, CtorShouldDefaultInitializedMirror)
{
    ImageData d{{"sheet1", {2, 2}}};
    ImageData expected;
    expected.sheetItem_ = {"sheet1", {2, 2}};
    expected.mirror_ = false;
    EXPECT_THAT(d, Eq(expected));
}

TEST(ImageDataTest, TestImageDataEqualToOperator)
{
    ImageData d1{{"sheet1", {0, 0}}};
    ImageData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.sheetItem_.sheetId_ = "mysheet";
    EXPECT_FALSE(d1 == d2);
}
}  // namespace Shared

}  // namespace FA
