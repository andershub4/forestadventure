/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "ByteStreamIf.h"

#include <iosfwd>
#include <memory>

namespace FA {

namespace Util {

class ByteStream : public ByteStreamIf
{
public:
    ByteStream(std::unique_ptr<std::istream> is);

    virtual std::string GetBuffer() const override;

private:
    std::unique_ptr<std::istream> is_;
};

}  // namespace Util

}  // namespace FA
