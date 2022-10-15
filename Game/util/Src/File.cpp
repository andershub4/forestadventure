/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "File.h"

#include <fstream>
#include <vector>

namespace FA {

std::string GetBuffer(std::istream& ifd)
{
    if (ifd.good()) {
        auto size = static_cast<unsigned long>(ifd.tellg());
        ifd.seekg(0, std::ios::beg);
        std::vector<char> buffer;
        buffer.resize(size);
        ifd.read(buffer.data(), size);
        std::string xmlBuffer(buffer.begin(), buffer.end());
        return xmlBuffer;
    }

    return {};
}

std::string GetFileBuffer(const std::string& fileName)
{
    std::ifstream ifd(fileName, std::ios::binary | std::ios::ate);
    return GetBuffer(ifd);
}

}  // namespace FA
