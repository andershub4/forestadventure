/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileHelper.h"

#include "File.h"
#include "Folder.h"

namespace FA {

namespace Tile {

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

std::string GetFileBuffer(const std::string& fileName)
{
    return FA::GetFileBuffer(fileName);
}

std::string GetHead(const std::string& filePath)
{
    return FA::GetHead(filePath);
}

}  // namespace Tile

}  // namespace FA
