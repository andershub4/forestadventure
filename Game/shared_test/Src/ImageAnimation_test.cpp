/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Animation/ImageAnimation.h"
#include "Mock/LoggerMock.h"
#include "Mock/SequenceMock.h"
#include "SpriteMock.h"
#include "TextureMock.h"

using namespace testing;

namespace FA {

namespace Shared {

class ImageAnimationTest : public testing::Test
{
protected:
    ImageAnimationTest()
        : seqMock_(std::make_shared<StrictMock<SequenceMock<Shared::Frame>>>())
        , animation_(seqMock_)
    {}

    Graphic::TextureMock textureMock_;
    sf::IntRect rect_{0, 0, 10, 12};
    Frame frame_{&textureMock_, rect_, {5, 6}};
    StrictMock<Graphic::SpriteMock> spriteMock_;
    StrictMock<LoggerMock> loggerMock_;
    std::shared_ptr<StrictMock<SequenceMock<Shared::Frame>>> seqMock_;
    ImageAnimation animation_;
};

TEST_F(ImageAnimationTest, ApplyToWithEmptyContentShouldDoNothing)
{
    EXPECT_CALL(*seqMock_, IsEmpty).WillOnce(Return(true));
    animation_.ApplyTo(spriteMock_, false);
}

TEST_F(ImageAnimationTest, ApplyToWithContentShouldSetTexture)
{
    EXPECT_CALL(*seqMock_, IsEmpty).WillOnce(Return(false));
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    animation_.ApplyTo(spriteMock_, false);
}

TEST_F(ImageAnimationTest, ApplyToWithContentAndCenterShouldSetTextureAndSetOrigin)
{
    EXPECT_CALL(*seqMock_, IsEmpty).WillOnce(Return(false));
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(spriteMock_, setTextureRect(Eq(rect_)));
    EXPECT_CALL(spriteMock_, setOrigin(5, 6));
    animation_.ApplyTo(spriteMock_, true);
}

TEST_F(ImageAnimationTest, AddFrameWithInvalidTextureShouldWarn)
{
    sf::IntRect rect{0, 0, 0, 12};
    Frame frame{nullptr, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));

    animation_.AddFrame(frame);
}

TEST_F(ImageAnimationTest, AddFrameWithInvalidWidthShouldWarn)
{
    sf::IntRect rect{0, 0, 0, 12};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));

    animation_.AddFrame(frame);
}

TEST_F(ImageAnimationTest, AddFrameWithInvalidHeightShouldWarn)
{
    sf::IntRect rect{0, 0, 10, 0};
    Frame frame{&textureMock_, rect};
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex(".*is invalid")));

    animation_.AddFrame(frame);
}

}  // namespace Shared

}  // namespace FA
