/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Format.h"

using namespace testing;

namespace FA {

TEST(FormatTest, ValidVaArgsShouldReturnString)
{
    int nCount = 3;
    auto str = ToString("%s: %d", "nCount", nCount);

    EXPECT_THAT(str, StrEq("nCount: 3"));
}

TEST(FormatTest, EmptyVaArgsShouldReturnEmptyString)
{
    auto str = ToString(nullptr);

    EXPECT_THAT(str, IsEmpty());
}

TEST(FormatTest, TooLongVaArgsShouldReturnTruncatedString)
{
    std::string longStr(40001, 'o');
    auto str = ToString("%s", longStr.c_str());

    EXPECT_THAT(str, SizeIs(40000));
}

}  // namespace FA
