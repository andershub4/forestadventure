/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>
#include <vector>

namespace FA {

namespace Tile {

struct FrameData;
struct Image;

class BasicTileSet
{
public:
    BasicTileSet();
    virtual ~BasicTileSet();

    virtual void Create() = 0;
    virtual std::vector<Image> GetImages() const = 0;
    virtual std::unordered_map<int, FrameData> GetFrameDatas() const = 0;
};

}  // namespace Tile

}  // namespace FA
