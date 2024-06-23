/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "Sequence.h"

using namespace testing;

namespace FA {

namespace Shared {

class SequenceTest : public testing::Test
{
protected:
    SequenceTest()
        : seq_(switchTime_)
    {}

    const float switchTime_ = 0.01f;
    const float deltaTimeToMakeAdvancement_ = switchTime_;
    const float deltaTimeToNotMakeAdvancement_ = switchTime_ / 2.0f;
    StrictMock<LoggerMock> loggerMock_;
    Sequence<int> seq_;
};

TEST_F(SequenceTest, GetCurrentWithNoElementsShouldReturnZeroInitialization)
{
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't start sequence, no elements"));
    seq_.Start();
    seq_.Update(deltaTimeToMakeAdvancement_);
    auto e = seq_.GetCurrent();

    EXPECT_THAT(e, Eq(int{}));
}

TEST_F(SequenceTest, GetCurrentWithoutUpdateWithSingleElementShouldReturnThatElement)
{
    seq_.Add(3);
    seq_.Start();
    auto e = seq_.GetCurrent();

    EXPECT_THAT(e, Eq(3));
}

TEST_F(SequenceTest, GetCurrentWithSingleElementShouldReturnThatElement)
{
    seq_.Add(3);
    seq_.Start();
    seq_.Update(deltaTimeToMakeAdvancement_);
    auto e1 = seq_.GetCurrent();

    EXPECT_THAT(e1, Eq(3));
    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e2 = seq_.GetCurrent();

    EXPECT_THAT(e2, Eq(3));
}

TEST_F(SequenceTest, GetCurrentWithoutUpdateWithMultipleElementsShouldReturnFirstElement)
{
    seq_.Add(4);
    seq_.Add(120);
    seq_.Start();

    auto e1 = seq_.GetCurrent();
    EXPECT_THAT(e1, Eq(4));
    auto e2 = seq_.GetCurrent();
    EXPECT_THAT(e2, Eq(4));
}

TEST_F(SequenceTest, GetCurrentWithMultipleElementsShouldAdvanceAndWrapAroundToDefaultIndex0)
{
    seq_.Add(123);
    seq_.Add(134);
    seq_.Start();

    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e1 = seq_.GetCurrent();
    EXPECT_THAT(e1, Eq(134));

    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e2 = seq_.GetCurrent();
    EXPECT_THAT(e2, Eq(123));
}

TEST_F(SequenceTest, StopShouldRestoreToDefaultIndex0AndNotAdvance)
{
    seq_.Add(111);
    seq_.Add(222);
    seq_.Start();

    seq_.Update(deltaTimeToMakeAdvancement_);
    auto e1 = seq_.GetCurrent();
    EXPECT_THAT(e1, Eq(222));

    seq_.Stop();
    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e2 = seq_.GetCurrent();
    EXPECT_THAT(e2, Eq(111));

    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e3 = seq_.GetCurrent();
    EXPECT_THAT(e3, Eq(111));
}

TEST_F(SequenceTest, GetCurrentWithMultipleElementsWhenSequenceNotStartedShouldNotAdvance)
{
    seq_.Add(3);
    seq_.Add(12);
    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e = seq_.GetCurrent();
    EXPECT_THAT(e, Eq(3));
}

TEST_F(SequenceTest, UpdateWithMultipleElementsWithDeltaTimeLesserThanSwitchTimeShouldNotAdvance)
{
    seq_.Add(4);
    seq_.Add(5);
    seq_.Start();
    seq_.Update(deltaTimeToNotMakeAdvancement_);

    auto e = seq_.GetCurrent();
    EXPECT_THAT(e, Eq(4));
}

TEST_F(SequenceTest, AddShouldNotInsertNewElementWhenSequenceIsStarted)
{
    seq_.Add(3);
    seq_.Add(12);
    seq_.Start();
    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e1 = seq_.GetCurrent();
    EXPECT_THAT(e1, Eq(12));

    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't add element when sequence is started"));
    seq_.Add(111);
    seq_.Update(deltaTimeToMakeAdvancement_);

    auto e2 = seq_.GetCurrent();
    EXPECT_THAT(e2, Eq(3));
}

TEST_F(SequenceTest, IsEmptyWithNoElementsShouldReturnTrue)
{
    EXPECT_TRUE(seq_.IsEmpty());
}

TEST_F(SequenceTest, IsEmptyWithTwoElementsShouldReturnFalse)
{
    seq_.Add(111);
    EXPECT_FALSE(seq_.IsEmpty());
}

TEST_F(SequenceTest, IsCompletedWithNoElementsShouldAlwaysReturnTrue)
{
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("Can't start sequence, no elements"));
    seq_.Start();
    EXPECT_TRUE(seq_.IsCompleted());
    seq_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_TRUE(seq_.IsCompleted());
}

TEST_F(SequenceTest, IsCompletedWithSingleElementShouldAlwaysReturnTrue)
{
    seq_.Add(3);
    seq_.Start();
    EXPECT_TRUE(seq_.IsCompleted());
    seq_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_TRUE(seq_.IsCompleted());
    seq_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_TRUE(seq_.IsCompleted());
}

TEST_F(SequenceTest, IsCompletedWithMultipleElementShouldReturnTrueAfterWrapAround)
{
    seq_.Add(3);
    seq_.Add(121);
    seq_.Start();
    EXPECT_FALSE(seq_.IsCompleted());
    seq_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_FALSE(seq_.IsCompleted());
    seq_.Update(deltaTimeToMakeAdvancement_);
    EXPECT_TRUE(seq_.IsCompleted());
}

TEST_F(SequenceTest, IsCompletedWithMultipleElementShouldReturnFalseAfterNewStart)
{
    seq_.Add(3);
    seq_.Add(121);
    seq_.Start();
    seq_.Update(deltaTimeToMakeAdvancement_);
    seq_.Update(deltaTimeToMakeAdvancement_);
    seq_.Start();
    EXPECT_FALSE(seq_.IsCompleted());
}

}  // namespace Shared

}  // namespace FA
