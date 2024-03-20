/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "ByteStreamIf.h"

namespace FA {

namespace Util {

class ByteStreamMock : public ByteStreamIf
{
public:
    MOCK_METHOD(std::string, GetBuffer, (), (const override));
};

}  // namespace Util

}  // namespace FA
