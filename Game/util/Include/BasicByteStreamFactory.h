/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>

namespace FA {

class BasicByteStream;

class BasicByteStreamFactory
{
public:
    virtual ~BasicByteStreamFactory() = default;

    virtual std::unique_ptr<BasicByteStream> Create(const std::string& fileName) const = 0;
};

}  // namespace FA
