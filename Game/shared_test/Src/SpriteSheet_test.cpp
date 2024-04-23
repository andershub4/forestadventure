/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "Resource/SpriteSheet.h"
#include "Resource/TextureRect.h"

using namespace testing;

namespace FA {

namespace Shared {

class SpriteSheetTest : public testing::Test
{
protected:
    StrictMock<LoggerMock> loggerMock_;
};

TEST_F(SpriteSheetTest, AtInsideSheetShouldReturnValidRect)
{
    SpriteSheet s(111, {100, 100}, {10, 10});
    auto rect = s.At({2, 1});
    TextureRect expected(111, {20, 10}, {10, 10});
    EXPECT_TRUE(rect.isValid_);
    EXPECT_THAT(rect, Eq(expected));
}

TEST_F(SpriteSheetTest, AtOutsideSheetShouldReturnInvalidRect)
{
    SpriteSheet s(111, {100, 100}, {10, 10});
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("uvCoord.*20.*20.*is outside.*rectCount.*10.*10")));
    auto rect = s.At({20, 20});
    TextureRect expected{};
    EXPECT_FALSE(rect.isValid_);
    EXPECT_THAT(rect, expected);
}

TEST_F(SpriteSheetTest, AtInsideEmptySheetShouldReturnInvalidRect)
{
    SpriteSheet s;
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("Invalid sheet.*textureSize.*0.*0.*rectCount.*0.*0")));
    auto rect = s.At({0, 0});
    TextureRect expected{};
    EXPECT_FALSE(rect.isValid_);
    EXPECT_THAT(rect, expected);
}

TEST_F(SpriteSheetTest, AtInsideInvalidSheetShouldReturnInvalidRect)
{
    SpriteSheet s(111, {0, 0}, {10, 10});
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("Invalid sheet.*textureSize.*0.*0.*rectCount.*10.*10")));
    auto rect = s.At({2, 1});
    TextureRect expected{};
    EXPECT_FALSE(rect.isValid_);
    EXPECT_THAT(rect, Eq(expected));
}

TEST_F(SpriteSheetTest, AtInsideInvalidSheetShouldReturnInvalidRect2)
{
    SpriteSheet s(111, {10, 10}, {100, 100});
    EXPECT_CALL(loggerMock_,
                MakeErrorLogEntry(ContainsRegex("Invalid sheet.*textureSize.*10.*10.*rectCount.*100.*100")));
    auto rect = s.At({2, 1});
    TextureRect expected{};
    EXPECT_FALSE(rect.isValid_);
    EXPECT_THAT(rect, Eq(expected));
}

}  // namespace Shared

}  // namespace FA
