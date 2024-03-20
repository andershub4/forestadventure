/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "ByteStreamFactoryIf.h"

namespace FA {

namespace Util {

class ByteStreamIf;

class ByteStreamFactory : public ByteStreamFactoryIf
{
public:
    ByteStreamFactory();
    ~ByteStreamFactory();

    virtual std::unique_ptr<ByteStreamIf> Create(const std::string& fileName) const override;
};

}  // namespace Util

}  // namespace FA
