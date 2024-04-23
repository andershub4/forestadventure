/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "Mock/SpriteSheetMock.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureRect.h"

using namespace testing;

namespace FA {

namespace Shared {

class SheetManagerTest : public testing::Test
{
protected:
    SheetManagerTest()
        : sheetMockProxy_(std::make_unique<SpriteSheetMockProxy>(sheetMock_))
        , rect1_(3142, {0, 0}, {10, 10})
        , mirrorRect1_(3142, {10, 0}, {-10, 10})
    {}

    SheetManager sheetManager_;
    StrictMock<LoggerMock> loggerMock_;
    SpriteSheetMock sheetMock_;
    std::unique_ptr<SpriteSheetMockProxy> sheetMockProxy_;
    TextureRect rect1_;
    TextureRect mirrorRect1_;
};

TEST_F(SheetManagerTest, MakeRectShouldReturnInvalidRectDueToSheetIdNotFound)
{
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex(".*mysheetId.*not found")));
    auto result = sheetManager_.MakeRect({"mysheetId", {1, 1}});
    TextureRect expected;
    EXPECT_FALSE(result.isValid_);
    EXPECT_THAT(result, Eq(expected));
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

TEST_F(SheetManagerTest, MakeRectWithMirrorEnabledShouldReturnValidRect)
{
    ImageData data{"blackEnemyId", {23, 33}, true};
    sheetManager_.AddSheet("blackEnemyId", std::move(sheetMockProxy_));
    EXPECT_CALL(sheetMock_, At(Eq(sf::Vector2u(23, 33)))).WillOnce(Return(rect1_));
    auto result = sheetManager_.MakeRect(data);
    TextureRect expected = mirrorRect1_;
    EXPECT_THAT(result, Eq(expected));
}

}  // namespace Shared

}  // namespace FA
