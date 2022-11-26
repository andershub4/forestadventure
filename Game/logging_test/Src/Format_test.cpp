/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Format.h"

using namespace testing;

namespace LogLib {

TEST(FormatTest, FormatToStringShouldSucceed)
{
    int nCount = 3;
    auto str = Format::ToString("nCount: %d", nCount);

    EXPECT_THAT(str, StrEq("nCount: 3"));
}

}  // namespace LogLib
