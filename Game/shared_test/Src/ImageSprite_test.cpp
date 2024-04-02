/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "SpriteMock.h"
#include "Sprites/ImageSprite.h"
#include "TextureMock.h"

using namespace testing;

namespace FA {

namespace Shared {

class ImageSpriteTest : public testing::Test
{
protected:
    ImageSpriteTest()
        : spriteMock_(std::make_shared<StrictMock<Graphic::SpriteMock>>())
    {}

protected:
    Graphic::TextureMock textureMock_;
    sf::IntRect rect_{0, 0, 10, 12};
    StrictMock<LoggerMock> loggerMock_;
    Frame frame_{&textureMock_, rect_};
    std::shared_ptr<StrictMock<Graphic::SpriteMock>> spriteMock_;
};

TEST_F(ImageSpriteTest, CtorShouldSetTexture)
{
    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    ImageSprite sprite_(spriteMock_, frame_);
}

TEST_F(ImageSpriteTest, CtorWithInvalidTextureShouldWarn)
{
    Frame frame{nullptr, rect_};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    ImageSprite sprite(spriteMock_, frame);
}

TEST_F(ImageSpriteTest, CtorWithInvalidWidthShouldWarn)
{
    sf::IntRect rect{0, 0, 0, 12};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    ImageSprite sprite(spriteMock_, frame);
}

TEST_F(ImageSpriteTest, CtorWithInvalidHeightShouldNotWarn)
{
    sf::IntRect rect{0, 0, 10, 0};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    ImageSprite sprite(spriteMock_, frame);
}

}  // namespace Shared

}  // namespace FA
