/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicByteStreamFactory.h"

namespace FA {

namespace Util {

class BasicByteStream;

class ByteStreamFactory : public BasicByteStreamFactory
{
public:
    ByteStreamFactory();
    ~ByteStreamFactory();

    virtual std::unique_ptr<BasicByteStream> Create(const std::string& fileName) const override;
};

}  // namespace Util

}  // namespace FA
