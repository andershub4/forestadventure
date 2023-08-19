/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LogMock.h"
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

TEST_F(SpriteSheetTest, DefaultConstructorGivesInvalidSheet)
{
    SpriteSheet s;
    EXPECT_FALSE(s.IsValid());
}

TEST_F(SpriteSheetTest, ConstructorGivesValidSheet)
{
    SpriteSheet s(111, {100, 100}, {10, 10});
    EXPECT_TRUE(s.IsValid());
}

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

TEST_F(SpriteSheetTest, ScanThreeRectsShouldReturnThreeRects)
{
    SpriteSheet s(111, {100, 100}, {10, 10});
    auto rects = s.Scan({0, 0}, 3);
    ASSERT_THAT(rects, SizeIs(3));
    TextureRect expected1(111, {0, 0}, {10, 10});
    TextureRect expected2(111, {10, 0}, {10, 10});
    TextureRect expected3(111, {20, 0}, {10, 10});
    EXPECT_THAT(rects, ElementsAre(expected1, expected2, expected3));
}

TEST_F(SpriteSheetTest, ScanOneRectOutsideSheetShouldReturnZeroRects)
{
    SpriteSheet s(111, {100, 100}, {10, 10});
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("uvCoord.*11.*11.*is outside.*rectCount.*10.*10")));
    auto rects = s.Scan({11, 11}, 1);
    EXPECT_THAT(rects, SizeIs(0));
}

TEST_F(SpriteSheetTest, AtShouldReturnInvalidRectWhenInvalidSheet)
{
    SpriteSheet s(111, {0, 0}, {10, 10});
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("Invalid sheet.*textureSize.*0.*0.*rectCount.*10.*10")));
    auto rect = s.At({2, 1});
    TextureRect expected{};
    EXPECT_FALSE(rect.isValid_);
    EXPECT_THAT(rect, Eq(expected));
}

TEST_F(SpriteSheetTest, AtShouldReturnInvalidRectWhenRectsSizeIsInvalid)
{
    SpriteSheet s(111, {10, 10}, {100, 100});
    EXPECT_CALL(loggerMock_,
                MakeErrorLogEntry(ContainsRegex("Invalid sheet.*textureSize.*10.*10.*rectCount.*100.*100")));
    auto rect = s.At({2, 1});
    TextureRect expected{};
    EXPECT_FALSE(rect.isValid_);
    EXPECT_THAT(rect, Eq(expected));
}

TEST_F(SpriteSheetTest, ScanEntireSheetShouldReturnMaxAvailableRects)
{
    SpriteSheet s(111, {100, 100}, {10, 10});
    auto rects = s.Scan({0, 0}, 10);
    EXPECT_THAT(rects, SizeIs(10));
}

TEST_F(SpriteSheetTest, ScanOutsideEntireSheetShouldReturnMaxAvailableRects)
{
    SpriteSheet s(111, {100, 100}, {10, 10});

    EXPECT_CALL(loggerMock_,
                MakeErrorLogEntry(ContainsRegex("Scan is outside.*rectCount.*10.*10.*uvCoord.*0.*0.*nRects.*11")));
    auto rects = s.Scan({0, 0}, 11);
    EXPECT_THAT(rects, SizeIs(10));
}

TEST_F(SpriteSheetTest, MirrorShouldSucceed)
{
    std::vector<TextureRect> input{TextureRect(1, {0, 0}, {10, 10}), TextureRect(2, {10, 10}, {10, 10}),
                                   TextureRect(3, {20, 20}, {10, 10})};
    std::vector<TextureRect> expected{TextureRect(1, {10, 0}, {-10, 10}), TextureRect(2, {20, 10}, {-10, 10}),
                                      TextureRect(3, {30, 20}, {-10, 10})};

    auto result = SpriteSheet::MirrorX(input);

    EXPECT_THAT(result, Eq(expected));
}

TEST_F(SpriteSheetTest, MirrorZeroRects)
{
    std::vector<TextureRect> input;
    std::vector<TextureRect> expected;
    auto result = SpriteSheet::MirrorX(input);

    EXPECT_THAT(result, IsEmpty());
}

}  // namespace Shared

}  // namespace FA
