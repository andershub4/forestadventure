/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Animation/ImageAnimation.h"
#include "Mock/SequenceMock.h"

using namespace testing;

namespace FA {

namespace Shared {

struct TestFrame
{
    int value_{};
    int centerValue_{};
};

class DrawableMock
{
public:
    MOCK_METHOD(void, SetValue, (int));
    MOCK_METHOD(void, SetCenterValue, (int));
};

template <>
struct AnimationTraits<Shared::TestFrame>
{
    using DrawableT = DrawableMock;
    static void Apply(const TestFrame& frame, DrawableMock& drawable, bool center)
    {
        drawable.SetValue(frame.value_);
        if (center) {
            drawable.SetCenterValue(frame.centerValue_);
        }
    }
};

class ImageAnimationTest : public testing::Test
{
protected:
    ImageAnimationTest()
        : seqMock_(std::make_shared<StrictMock<SequenceMock<TestFrame>>>())
    {}

    std::shared_ptr<ImageAnimation<TestFrame>> CreateAnimationWithEmptyContent(
        std::shared_ptr<StrictMock<SequenceMock<TestFrame>>> seqMock)
    {
        EXPECT_CALL(*seqMock, IsEmpty).WillOnce(Return(true));
        return std::make_shared<ImageAnimation<TestFrame>>(seqMock);
    }
    std::shared_ptr<ImageAnimation<TestFrame>> CreateAnimation(
        std::shared_ptr<StrictMock<SequenceMock<TestFrame>>> seqMock)
    {
        EXPECT_CALL(*seqMock, IsEmpty).WillOnce(Return(false));
        return std::make_shared<ImageAnimation<TestFrame>>(seqMock);
    }

    TestFrame frame_{42, 43};
    DrawableMock drawableMock_;
    std::shared_ptr<StrictMock<SequenceMock<TestFrame>>> seqMock_;
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
    EXPECT_CALL(drawableMock_, SetValue(42));
    animation->ApplyTo(drawableMock_);
}

TEST_F(ImageAnimationTest, UpdateAndApplyWithContentAndCenterShoulSetTextureAndSetOrigin)
{
    auto animation = CreateAnimation(seqMock_);
    animation->Center();
    EXPECT_CALL(*seqMock_, Update(_));
    animation->Update(0.01f);
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(drawableMock_, SetValue(42));
    EXPECT_CALL(drawableMock_, SetCenterValue(43));
    animation->ApplyTo(drawableMock_);
}

TEST_F(ImageAnimationTest, RegisterUpdateCBShouldBeCalledDuringUpdate)
{
    auto animation = CreateAnimation(seqMock_);
    MockFunction<void(const ImageAnimationIf<TestFrame>&)> callbackFunctionMock;
    animation->RegisterUpdateCB(callbackFunctionMock.AsStdFunction());
    EXPECT_CALL(*seqMock_, Update(0.01f));
    EXPECT_CALL(callbackFunctionMock, Call(Ref(*animation)));
    animation->Update(0.01f);
}

}  // namespace Shared

}  // namespace FA
