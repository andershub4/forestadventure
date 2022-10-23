/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gtest/gtest.h>

#include <fstream>

#include "ByteStream.h"

using namespace testing;

namespace FA {

TEST(ByteStreamTest, GetBufferShouldReturnStringContent)
{
    std::string expected{"Hello file!"};
    ByteStream byteStream(std::make_unique<std::istringstream>(expected));
    auto result = byteStream.GetBuffer();

    EXPECT_EQ(expected, result);
}

}  // namespace FA
