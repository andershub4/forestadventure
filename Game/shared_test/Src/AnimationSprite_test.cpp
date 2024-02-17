/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LogMock.h"
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
        : spriteMock_(std::make_shared<StrictMock<Graphic::SpriteMock>>())
        , sprite_(spriteMock_, 0, switchTime_)
    {}

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
    std::shared_ptr<StrictMock<Graphic::SpriteMock>> spriteMock_;
    StrictMock<LoggerMock> loggerMock_;
    AnimationSprite sprite_;
};

TEST_F(AnimationSpriteTest, UpdateWithNoTextureShouldDoNothing)
{
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't start animation, no frames"));
    sprite_.Start();
    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, UpdateWithInvalidDefaultIndexShouldDoNothing)
{
    sprite_ = AnimationSprite(spriteMock_, 10, switchTime_);
    sprite_.AddFrame(frame_);

    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't start animation, defaultIndex 10 is invalid"));
    sprite_.Start();

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, UpdateWithInvalidFrameShouldDoNothing)
{
    sf::IntRect rect{0, 0, 10, 0};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));
    sprite_.AddFrame(frame);

    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't start animation, no frames"));
    sprite_.Start();

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, UpdateWithSingleTextureShouldSetSameTexture)
{
    sprite_.AddFrame(frame_);
    sprite_.Start();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, UpdateWithMultipleTextureShouldAdvanceAndWrapAroundToDefaultIndex0)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect2_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, UpdateWithMultipleTextureShouldAdvanceAndWrapAroundToDefaultIndex1)
{
    sprite_ = AnimationSprite(spriteMock_, 1, switchTime_);
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect2_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, StopShouldRestoreToDefaultIndex0AndNotAdvance)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect2_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);

    sprite_.Stop();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, StopShouldRestoreToDefaultIndex1AndNotAdvance)
{
    sprite_ = AnimationSprite(spriteMock_, 1, switchTime_);
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);

    sprite_.Stop();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect2_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect2_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, UpdateWithMultipleTextureWhenAnimationNotStartedShouldNotAdvance)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

TEST_F(AnimationSpriteTest, UpdateWithMultipleTextureWithDeltaTimeLesserThanSwitchTimeShouldNotAdvance)
{
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.Start();

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToNotMakeAdvancement_);
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

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock2_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect2_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);

    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't add frame during animation"));
    sprite_.AddFrame(frame3_);

    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(deltaTimeToMakeAdvancement_);
}

class AnimationSpriteTestP : public AnimationSpriteTest, public WithParamInterface<unsigned int>
{
};

INSTANTIATE_TEST_CASE_P(AnimationSpriteTests, AnimationSpriteTestP, Values(0u, 1u, 2u));

TEST_P(AnimationSpriteTestP, IsCompletedShouldReturnTrueWhenWrappedAround)
{
    unsigned int defaultIndex = GetParam();
    sprite_ = AnimationSprite(spriteMock_, defaultIndex, switchTime_);
    sprite_.AddFrame(frame_);
    sprite_.AddFrame(frame2_);
    sprite_.AddFrame(frame3_);
    sprite_.Start();

    EXPECT_CALL(*spriteMock_, setTextureImpl(_, false)).Times(3);
    EXPECT_CALL(*spriteMock_, setTextureRect(_)).Times(3);

    sprite_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_FALSE(sprite_.IsCompleted());

    sprite_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_FALSE(sprite_.IsCompleted());

    sprite_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_TRUE(sprite_.IsCompleted());
}

}  // namespace Shared

}  // namespace FA
