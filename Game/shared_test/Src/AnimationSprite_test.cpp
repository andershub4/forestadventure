/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "Mock/SequenceMock.h"
#include "SpriteMock.h"
#include "Sprites/AnimationSprite.h"
#include "TextureMock.h"

using namespace testing;

namespace FA {

namespace Shared {

class AnimationSpriteTest : public testing::Test
{
protected:
    AnimationSpriteTest()
        : seqMock_(std::make_shared<StrictMock<SequenceMock<Shared::Frame>>>())
        , sprite_(seqMock_)
    {}

    Graphic::TextureMock textureMock_;
    sf::IntRect rect_{0, 0, 10, 12};
    Frame frame_{&textureMock_, rect_};
    StrictMock<Graphic::SpriteMock> spriteMock_;
    StrictMock<LoggerMock> loggerMock_;
    std::shared_ptr<StrictMock<SequenceMock<Shared::Frame>>> seqMock_;
    AnimationSprite sprite_;
};

TEST_F(AnimationSpriteTest, ApplyToWithInvalidFrameShouldDoNothing)
{
    Shared::Frame invalid{};
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(invalid));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, ApplyToWithValidFrameShouldSetTexture)
{
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, AddFrameWithInvalidTextureShouldWarn)
{
    sf::IntRect rect{0, 0, 0, 12};
    Frame frame{nullptr, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));

    sprite_.AddFrame(frame);
}

TEST_F(AnimationSpriteTest, AddFrameWithInvalidWidthShouldWarn)
{
    sf::IntRect rect{0, 0, 0, 12};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));

    sprite_.AddFrame(frame);
}

TEST_F(AnimationSpriteTest, AddFrameWithInvalidHeightShouldWarn)
{
    sf::IntRect rect{0, 0, 10, 0};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));

    sprite_.AddFrame(frame);
}

}  // namespace Shared

}  // namespace FA
