/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Animation/ImageAnimation.h"
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
        : seqMock_(std::make_shared<StrictMock<SequenceMock<Shared::ImageFrame>>>())
        , animation_(seqMock_)
    {}

    Graphic::TextureMock textureMock_;
    sf::IntRect rect_{0, 0, 10, 12};
    ImageFrame frame_{&textureMock_, rect_, {5, 6}};
    StrictMock<Graphic::SpriteMock> spriteMock_;
    std::shared_ptr<StrictMock<SequenceMock<Shared::ImageFrame>>> seqMock_;
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

}  // namespace Shared

}  // namespace FA
