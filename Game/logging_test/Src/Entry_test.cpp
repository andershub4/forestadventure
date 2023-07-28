/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Entry.h"

using namespace testing;

namespace LogLib {

TEST(EntryTest, EntryEqualToOperator)
{
    Entry a{LogLevel::Debug, "myFunc", "in here"};
    auto b = a;
    EXPECT_TRUE(a == b);

    Entry c{LogLevel::Error, "myFunc", "in here"};
    EXPECT_FALSE(a == c);
}

TEST(EntryTest, ReturnStrShouldSucceed)
{
    Entry debugEntry{LogLevel::Debug, "myFunc", "nCount: 4"};
    auto str1 = debugEntry.Str();
    EXPECT_THAT(str1, StrEq("[DEBUG | myFunc]: nCount: 3"));

    Entry infoEntry{LogLevel::Info, "myFunc", "nCount: 3"};
    auto str2 = infoEntry.Str();
    EXPECT_THAT(str2, StrEq("[INFO | myFunc]: nCount: 3"));

    Entry warnEntry{LogLevel::Warn, "myFunc", "nCount: 3"};
    auto str3 = warnEntry.Str();
    EXPECT_THAT(str3, StrEq("[WARNING | myFunc]: nCount: 3"));

    Entry errorEntry{LogLevel::Error, "myFunc", "nCount: 3"};
    auto str4 = errorEntry.Str();
    EXPECT_THAT(str4, StrEq("[ERROR | myFunc]: nCount: 3"));
}

}  // namespace LogLib
