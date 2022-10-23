/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ByteStream.h"

#include <istream>
#include <vector>

namespace FA {

ByteStream::ByteStream(std::unique_ptr<std::istream> is)
    : is_(std::move(is))
{}

std::string ByteStream::GetBuffer() const
{
    if (is_->good()) {
        is_->seekg(0, is_->end);
        int size = static_cast<unsigned long>(is_->tellg());
        is_->seekg(0, is_->beg);
        std::vector<char> buffer;
        buffer.resize(size);
        is_->read(buffer.data(), size);
        std::string xmlBuffer(buffer.begin(), buffer.end());
        return xmlBuffer;
    }

    return {};
}

}  // namespace FA
