/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Animation/Animation.h"
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

class AnimationTest : public testing::Test
{
protected:
    AnimationTest()
        : seqMock_(std::make_shared<StrictMock<SequenceMock<TestFrame>>>())
    {}

    std::shared_ptr<Animation<TestFrame>> CreateAnimationWithEmptyContent(
        std::shared_ptr<StrictMock<SequenceMock<TestFrame>>> seqMock)
    {
        EXPECT_CALL(*seqMock, IsEmpty).WillOnce(Return(true));
        return std::make_shared<Animation<TestFrame>>(seqMock);
    }
    std::shared_ptr<Animation<TestFrame>> CreateAnimation(std::shared_ptr<StrictMock<SequenceMock<TestFrame>>> seqMock,
                                                          bool center)
    {
        EXPECT_CALL(*seqMock, IsEmpty).WillOnce(Return(false));
        return std::make_shared<Animation<TestFrame>>(seqMock, center);
    }

    TestFrame frame_{42, 43};
    DrawableMock drawableMock_;
    std::shared_ptr<StrictMock<SequenceMock<TestFrame>>> seqMock_;
};

TEST_F(AnimationTest, UpdateWithEmptyContentShouldDoNothing)
{
    auto animation = CreateAnimationWithEmptyContent(seqMock_);
    animation->Update(0.01f);
}

TEST_F(AnimationTest, ApplyWithEmptyContentShouldDoNothing)
{
    auto animation = CreateAnimationWithEmptyContent(seqMock_);
    animation->ApplyTo(drawableMock_);
}

TEST_F(AnimationTest, UpdateAndApplyWithContentShoulSetValue)
{
    auto animation = CreateAnimation(seqMock_, false);
    EXPECT_CALL(*seqMock_, Update(0.01f));
    animation->Update(0.01f);
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(drawableMock_, SetValue(42));
    animation->ApplyTo(drawableMock_);
}

TEST_F(AnimationTest, UpdateAndApplyWithContentAndCenterShoulSetValeAndSetCenterValue)
{
    auto animation = CreateAnimation(seqMock_, true);
    EXPECT_CALL(*seqMock_, Update(_));
    animation->Update(0.01f);
    EXPECT_CALL(*seqMock_, GetCurrent).WillOnce(Return(frame_));
    EXPECT_CALL(drawableMock_, SetValue(42));
    EXPECT_CALL(drawableMock_, SetCenterValue(43));
    animation->ApplyTo(drawableMock_);
}

}  // namespace Shared

}  // namespace FA
