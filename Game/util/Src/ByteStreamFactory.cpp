/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ByteStreamFactory.h"

#include <fstream>

#include "ByteStream.h"

namespace FA {

ByteStreamFactory::ByteStreamFactory() = default;

ByteStreamFactory::~ByteStreamFactory() = default;

std::unique_ptr<BasicByteStream> ByteStreamFactory::Create(const std::string &fileName) const
{
    auto ifd = std::make_unique<std::ifstream>(fileName, std::ios::binary);
    return std::make_unique<ByteStream>(std::move(ifd));
}

}  // namespace FA
