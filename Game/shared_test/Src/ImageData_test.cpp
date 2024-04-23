/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Resource/ImageData.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(ImageDataTest, CtorShouldDefaultInitializeRectAndMirror)
{
    ImageData d{"sheet1", {2, 2}};
    ImageData expected;
    expected.sheetId_ = "sheet1";
    expected.position_ = sf::Vector2u(2, 2);
    expected.mirror_ = false;
    expected.rect_ = sf::IntRect(0, 0, 0, 0);
    EXPECT_THAT(d, Eq(expected));
}

TEST(ImageDataTest, CtorShouldDefaultInitializeRect)
{
    ImageData d{"sheet1", {2, 2}, true};
    ImageData expected;
    expected.sheetId_ = "sheet1";
    expected.position_ = sf::Vector2u(2, 2);
    expected.mirror_ = true;
    expected.rect_ = sf::IntRect(0, 0, 0, 0);
    EXPECT_THAT(d, Eq(expected));
}

TEST(ImageDataTest, CtorShouldDefaultInitializeMirror)
{
    ImageData d{"sheet1", {2, 2}, {2, 2, 6, 6}};
    ImageData expected;
    expected.sheetId_ = "sheet1";
    expected.position_ = sf::Vector2u(2, 2);
    expected.mirror_ = false;
    expected.rect_ = sf::IntRect(2, 2, 6, 6);
    EXPECT_THAT(d, Eq(expected));
}

TEST(ImageDataTest, CtorShouldInitializeRectAndMirror)
{
    ImageData d{"sheet1", {2, 2}, true, {2, 2, 6, 6}};
    ImageData expected;
    expected.sheetId_ = "sheet1";
    expected.position_ = sf::Vector2u(2, 2);
    expected.mirror_ = true;
    expected.rect_ = sf::IntRect(2, 2, 6, 6);
    EXPECT_THAT(d, Eq(expected));
}

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
