/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Util {

class ByteStreamIf
{
public:
    virtual ~ByteStreamIf() = default;

    virtual std::string GetBuffer() const = 0;
};

}  // namespace Util

}  // namespace FA
