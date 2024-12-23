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
        , spriteMock_(std::make_shared<StrictMock<Graphic::SpriteMock>>())
    {}

    std::shared_ptr<ImageAnimation> CreateAnimationWithEmptyContent(
        std::shared_ptr<StrictMock<SequenceMock<Shared::ImageFrame>>> seqMock)
    {
        EXPECT_CALL(*seqMock, IsEmpty).WillOnce(Return(true));
        return std::make_shared<ImageAnimation>(seqMock);
    }
    std::shared_ptr<ImageAnimation> CreateAnimation(
        std::shared_ptr<StrictMock<SequenceMock<Shared::ImageFrame>>> seqMock)
    {
        EXPECT_CALL(*seqMock, IsEmpty).WillOnce(Return(false));
        return std::make_shared<ImageAnimation>(seqMock);
    }

    StrictMock<Graphic::TextureMock> textureMock_;
    sf::IntRect rect_{0, 0, 10, 12};
    ImageFrame frame_{&textureMock_, rect_, {5, 6}};
    std::shared_ptr<StrictMock<Graphic::SpriteMock>> spriteMock_;
    std::shared_ptr<StrictMock<SequenceMock<Shared::ImageFrame>>> seqMock_;
};

TEST_F(ImageAnimationTest, UpdateWithEmptyContentShouldDoNothing)
{
    auto animation = CreateAnimationWithEmptyContent(seqMock_);
    animation->Update(0.01f);
}

TEST_F(ImageAnimationTest, UpdateAndApplyWithContentShoulSetTexture)
{
    auto animation = CreateAnimation(seqMock_);
    EXPECT_CALL(*seqMock_, Update(0.01f));
    animation->Update(0.01f);
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));
    animation->ApplyTo(spriteMock_);
}

TEST_F(ImageAnimationTest, UpdateAndApplyWithContentAndCenterShoulSetTextureAndSetOrigin)
{
    auto animation = CreateAnimation(seqMock_);
    animation->Center();
    EXPECT_CALL(*seqMock_, Update(_));
    animation->Update(0.01f);
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(*spriteMock_, setTextureImpl(_, _));
    EXPECT_CALL(*spriteMock_, setTextureRect(_));
    EXPECT_CALL(*spriteMock_, setOrigin(5, 6));
    animation->ApplyTo(spriteMock_);
}

TEST_F(ImageAnimationTest, RegisterUpdateCBShouldBeCalledDuringUpdate)
{
    auto animation = CreateAnimation(seqMock_);
    MockFunction<void(const ImageAnimationIf&)> callbackFunctionMock;
    animation->RegisterUpdateCB(callbackFunctionMock.AsStdFunction());
    EXPECT_CALL(*seqMock_, Update(0.01f));
    EXPECT_CALL(callbackFunctionMock, Call(Ref(*animation)));
    animation->Update(0.01f);
}

}  // namespace Shared

}  // namespace FA
