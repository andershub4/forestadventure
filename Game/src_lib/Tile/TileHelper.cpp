/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileHelper.h"

namespace FA {

namespace Tile {

namespace {

// TODO: Consider to use fn from folder.h instead when util unit is created
std::string GetHead(const std::string& filePath)
{
    std::string result;
    const size_t index = filePath.find_last_of("\\/");

    if (index != std::string::npos) {
        result = filePath.substr(0, index);
    }

    return result;
}

}  // namespace

std::string GetFilePath(const std::string& baseDir, const std::string& source)
{
    auto head = baseDir;
    auto tail = source;

    const std::string moveBackMatch = "../";
    auto index = tail.find(moveBackMatch);
    while (index != std::string::npos) {
        head = GetHead(head);
        tail = tail.substr(index + moveBackMatch.size());
        index = tail.find(moveBackMatch);
    }

    return head + '/' + tail;
}

}  // namespace Tile

}  // namespace FA
