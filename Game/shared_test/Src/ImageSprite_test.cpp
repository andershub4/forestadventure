/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

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
    Graphic::TextureMock textureMock_;
    sf::IntRect rect_{0, 0, 10, 12};
    StrictMock<LoggerMock> loggerMock_;
    Frame frame_{&textureMock_, rect_};
    StrictMock<Graphic::SpriteMock> spriteMock_;
};

TEST_F(ImageSpriteTest, ApplyToShouldSetTexture)
{
    ImageSprite sprite_(frame_);
    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(ImageSpriteTest, CtorWithInvalidTextureShouldWarn)
{
    Frame frame{nullptr, rect_};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    ImageSprite sprite(frame);
    sprite.ApplyTo(spriteMock_);
}

TEST_F(ImageSpriteTest, CtorWithInvalidWidthShouldWarn)
{
    sf::IntRect rect{0, 0, 0, 12};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    ImageSprite sprite(frame);
    sprite.ApplyTo(spriteMock_);
}

TEST_F(ImageSpriteTest, CtorWithInvalidHeightShouldNotWarn)
{
    sf::IntRect rect{0, 0, 10, 0};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    ImageSprite sprite(frame);
    sprite.ApplyTo(spriteMock_);
}

}  // namespace Shared

}  // namespace FA
