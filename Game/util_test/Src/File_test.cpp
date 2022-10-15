/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include "File.h"

using namespace testing;

namespace FA {

TEST(FileTest, GetBufferShouldReturnStringContent)
{
    std::string expected{"Hello file!"};
    std::istringstream ss(expected);
    auto result = GetBuffer(ss);

    EXPECT_EQ(expected, result);
}

}  // namespace FA
