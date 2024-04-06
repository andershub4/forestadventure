/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "SpriteMock.h"
#include "Sprites/AnimationSprite.h"
#include "TextureMock.h"

using namespace testing;

namespace FA {

namespace Shared {

class AnimationSpriteTest : public testing::Test
{
protected:
    const float switchTime_ = 0.01f;
    const float deltaTimeToMakeAdvancement_ = switchTime_;
    const float deltaTimeToNotMakeAdvancement_ = switchTime_ / 2.0f;
    Graphic::TextureMock textureMock_;
    Graphic::TextureMock textureMock2_;
    Graphic::TextureMock textureMock3_;
    sf::IntRect rect_{0, 0, 10, 12};
    sf::IntRect rect2_{10, 0, 10, 12};
    sf::IntRect rect3_{20, 0, 10, 12};
    Frame frame_{&textureMock_, rect_};
    Frame frame2_{&textureMock2_, rect2_};
    Frame frame3_{&textureMock3_, rect3_};
    StrictMock<Graphic::SpriteMock> spriteMock_;
    StrictMock<LoggerMock> loggerMock_;
    AnimationSprite sprite_{switchTime_};
};

TEST_F(AnimationSpriteTest, ApplyToWithNoFrameShouldDoNothing)
{
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't start animation, no frames"));
    sprite_.Start();
    sprite_.Update(deltaTimeToMakeAdvancement_);
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, ApplyToWithInvalidFrameShouldDoNothing)
{
    sf::IntRect rect{0, 0, 10, 0};
    Frame invalidFrame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    sprite_.AddFrame(invalidFrame);

    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't start animation, no frames"));
    sprite_.Start();

    sprite_.Update(deltaTimeToMakeAdvancement_);
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, ApplyToWithoutUpdateWithSingleTextureShouldSetSameTexture)
{
    sprite_.AddFrame(frame_);
    sprite_.Start();

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, ApplyToWithSingleTextureShouldSetSameTexture)
{
    sprite_.AddFrame(frame_);
    sprite_.Start();
    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, ApplyToWithoutUpdateWithMultipleTextureShouldNotAdvance)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, ApplyToWithMultipleTextureShouldAdvanceAndWrapAroundToDefaultIndex0)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect2_)));
    sprite_.ApplyTo(spriteMock_);

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, StopShouldRestoreToDefaultIndex0AndNotAdvance)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    sprite_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect2_)));
    sprite_.ApplyTo(spriteMock_);

    sprite_.Stop();
    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, ApplyToWithMultipleTextureWhenAnimationNotStartedShouldNotAdvance)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

TEST_F(AnimationSpriteTest, UpdateWithMultipleTextureWithDeltaTimeLesserThanSwitchTimeShouldNotAdvance)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();
    sprite_.Update(deltaTimeToNotMakeAdvancement_);

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

TEST_F(AnimationSpriteTest, AddFrameShouldNotInsertNewFrameDuringAnimation)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();
    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect2_)));
    sprite_.ApplyTo(spriteMock_);

    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't add frame during animation"));
    sprite_.AddFrame(frame3_);
    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    sprite_.ApplyTo(spriteMock_);
}

}  // namespace Shared

}  // namespace FA
