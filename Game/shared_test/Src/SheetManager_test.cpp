/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "Resource/AnimationData.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureRect.h"
#include "Mock/SpriteSheetMock.h"

using namespace testing;

namespace FA {

namespace Shared {

class SheetManagerTest : public testing::Test
{
protected:
    SheetManagerTest()
        : sheetMockProxy_(std::make_unique<SpriteSheetMockProxy>(sheetMock_))
        , rect1_(3142, {0, 0}, {10, 10})
        , rect2_(3142, {10, 10}, {10, 10})
        , rects_{rect1_, rect2_}
        , mirrorRect1_(3142, {10, 0}, {-10, 10})
        , mirrorRect2_(3142, {20, 10}, {-10, 10})
        , mirrorRects_{mirrorRect1_, mirrorRect2_}
    {}

    SheetManager sheetManager_;
    StrictMock<LoggerMock> loggerMock_;
    SpriteSheetMock sheetMock_;
    std::unique_ptr<SpriteSheetMockProxy> sheetMockProxy_;
    TextureRect rect1_, rect2_;
    std::vector<TextureRect> rects_;
    TextureRect mirrorRect1_, mirrorRect2_;
    std::vector<TextureRect> mirrorRects_;
};

TEST_F(SheetManagerTest, MakeRectShouldReturnInvalidRectDueToSheetIdNotFound)
{
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex(".*mysheetId.*not found")));
    auto result = sheetManager_.MakeRect({"mysheetId", {1, 1}});
    TextureRect expected;
    EXPECT_FALSE(result.isValid_);
    EXPECT_THAT(result, Eq(expected));
}

TEST_F(SheetManagerTest, MakeRectsShouldReturnEmptyVectorDueToSheetIdNotFound)
{
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex(".*yoursheetId.*not found")));
    AnimationData data{"yoursheetId", {{0, 0}, 3, 0}, false};
    auto result = sheetManager_.MakeRects(data);
    EXPECT_THAT(result, SizeIs(0));
}

TEST_F(SheetManagerTest, MakeRectShouldReturnValidRect)
{
    ImageData data{"blackEnemyId", {23, 33}};
    sheetManager_.AddSheet("blackEnemyId", std::move(sheetMockProxy_));
    EXPECT_CALL(sheetMock_, At(Eq(sf::Vector2u(23, 33)))).WillOnce(Return(rect1_));
    auto result = sheetManager_.MakeRect(data);
    TextureRect expected = rect1_;
    EXPECT_THAT(result, Eq(expected));
}

TEST_F(SheetManagerTest, MakeRectsShouldReturnValidVector)
{
    AnimationData data{"whiteEnemyId", {{223, 122}, 2, 0}, false};
    sheetManager_.AddSheet("whiteEnemyId", std::move(sheetMockProxy_));
    EXPECT_CALL(sheetMock_, Scan(Eq(sf::Vector2u(223, 122)), Eq(2))).WillOnce(Return(rects_));
    auto result = sheetManager_.MakeRects(data);
    std::vector<TextureRect> expected = rects_;
    EXPECT_THAT(result, Eq(expected));
}

TEST_F(SheetManagerTest, MakeRectsWithMirrorEnabledShouldReturnValidVector)
{
    AnimationData data{"heroId", {{223, 122}, 2, 0}, true};
    sheetManager_.AddSheet("heroId", std::move(sheetMockProxy_));
    EXPECT_CALL(sheetMock_, Scan(Eq(sf::Vector2u(223, 122)), Eq(2))).WillOnce(Return(rects_));
    auto result = sheetManager_.MakeRects(data);
    std::vector<TextureRect> expected = mirrorRects_;
    EXPECT_THAT(result, Eq(expected));
}

}  // namespace Shared

}  // namespace FA
