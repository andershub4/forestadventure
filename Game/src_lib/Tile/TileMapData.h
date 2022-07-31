/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "FrameData.h"
#include "Image.h"

namespace FA {

namespace Tile {

struct TileMapData
{
    struct MapProperties
    {
        int width_{};
        int height_{};
        int tileWidth_{};
        int tileHeight_{};
    };

    struct TileSet
    {
        std::vector<Image> images_;
        std::unordered_map<int, FrameData> frameDatas_;
    };

    struct Layer
    {
        std::string name_{};
        std::vector<int> tileIds_;
    };

    struct Object
    {
        std::string typeStr_{};
        int x_{};
        int y_{};
        std::unordered_map<std::string, std::string> properties_;
    };

    struct ObjectGroup
    {
        std::string name_{};
        std::vector<Object> objects_;
    };

    MapProperties mapProperties_;
    std::map<int, TileSet, std::greater<int>> tileSets_;
    std::vector<Layer> layers_;
    std::vector<ObjectGroup> objectGroups_;
};

}  // namespace Tile

}  // namespace FA
