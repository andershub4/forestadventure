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
#include "Resource/SheetItem.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureRect.h"

using namespace testing;

namespace FA {

namespace Shared {

class SheetManagerTest : public testing::Test
{
protected:
    SheetManagerTest()
        : sheetMockProxy_(std::make_unique<StrictMock<SpriteSheetMockProxy>>(sheetMock_))
        , rect1_(3142, {0, 0, 10, 10})
    {}

    SheetManager sheetManager_;
    StrictMock<LoggerMock> loggerMock_;
    StrictMock<SpriteSheetMock> sheetMock_;
    std::unique_ptr<StrictMock<SpriteSheetMockProxy>> sheetMockProxy_;
    TextureRect rect1_;
};

TEST_F(SheetManagerTest, MakeRectShouldReturnInvalidRectDueToSheetIdNotFound)
{
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex(".*mysheetId.*not found")));
    auto result = sheetManager_.GetTextureRect({"mysheetId", {1, 1}});
    TextureRect expected;
    EXPECT_FALSE(result.isValid_);
    EXPECT_THAT(result, Eq(expected));
}

TEST_F(SheetManagerTest, MakeRectShouldReturnValidRect)
{
    SheetItem item{"blackEnemyId", {23, 33}};
    sheetManager_.AddSheet("blackEnemyId", std::move(sheetMockProxy_));
    EXPECT_CALL(sheetMock_, At(Eq(sf::Vector2u(23, 33)))).WillOnce(Return(rect1_));
    auto result = sheetManager_.GetTextureRect(item);
    TextureRect expected = rect1_;
    EXPECT_THAT(result, Eq(expected));
}

}  // namespace Shared

}  // namespace FA
