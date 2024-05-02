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

TEST(ColliderDataTest, CtorShouldDefaultInitializeRect)
{
    ColliderData d{"sheet1", {2, 2}};
    ColliderData expected;
    expected.sheetId_ = "sheet1";
    expected.position_ = sf::Vector2u(2, 2);
    expected.rect_ = sf::IntRect(0, 0, 0, 0);
    EXPECT_THAT(d, Eq(expected));
}

TEST(ColliderDataTest, CtorShouldInitializeRect)
{
    ColliderData d{"sheet1", {2, 2}, {2, 2, 6, 6}};
    ColliderData expected;
    expected.sheetId_ = "sheet1";
    expected.position_ = sf::Vector2u(2, 2);
    expected.rect_ = sf::IntRect(2, 2, 6, 6);
    EXPECT_THAT(d, Eq(expected));
}

TEST(ColliderDataTest, TestImageDataEqualToOperator)
{
    ColliderData d1{"sheet1", {0, 0}};
    ColliderData d2 = d1;
    EXPECT_TRUE(d1 == d2);
    d1.sheetId_ = "mysheet";
    EXPECT_FALSE(d1 == d2);
}
}  // namespace Shared

}  // namespace FA
