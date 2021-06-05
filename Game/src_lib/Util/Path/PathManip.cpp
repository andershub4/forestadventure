/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PathManip.h"

namespace FA {

namespace Util {

std::string GetHead(const std::string& filePath)
{
    std::string result;
    const size_t index = filePath.find_last_of("\\/");

    if (index != std::string::npos) {
        result = filePath.substr(0, index);
    }

    return result;
}

}  // namespace Util

}  // namespace FA
