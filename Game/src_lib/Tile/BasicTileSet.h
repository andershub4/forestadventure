/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

namespace FA {

namespace Tile {

struct FrameData;

class BasicTileSet
{
public:
    struct Image
    {
        std::string path_;
        int width_{};
        int height_{};
    };

    BasicTileSet();
    virtual ~BasicTileSet();

    virtual void Create() = 0;
    virtual std::vector<Image> GetImages() const = 0;
    virtual FrameData GetFrameData(int id) const = 0;

private:
    std::string name_;
};

}  // namespace Tile

}  // namespace FA
