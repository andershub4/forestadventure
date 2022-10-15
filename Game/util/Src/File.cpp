/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "File.h"

#include <fstream>
#include <vector>

namespace FA {

std::string GetBuffer(std::istream& is)
{
    if (is.good()) {
        is.seekg(0, is.end);
        int size = is.tellg();
        is.seekg(0, is.beg);  
        std::vector<char> buffer;
        buffer.resize(size);
        is.read(buffer.data(), size);
        std::string xmlBuffer(buffer.begin(), buffer.end());
        return xmlBuffer;
    }

    return {};
}

std::string GetFileBuffer(const std::string& fileName)
{
    std::ifstream ifd(fileName, std::ios::binary);
    return GetBuffer(ifd);
}

}  // namespace FA
