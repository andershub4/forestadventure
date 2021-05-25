/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <string>
#include <vector>

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

    MapProperties mapProperties_;

    struct TileSet
    {
        int tileWidth_{};
        int tileHeight_{};
        int columns_{};
        int tileCount_{};
        std::string textureFilePath_;
        int firstGid_{};
    };

    std::vector<TileSet> tileSets_;

    struct Layer
    {
        std::string name_{};
        std::vector<int> tileIds_;
    };

    std::vector<Layer> layers_;

    struct Object
    {
        std::string typeStr_{};
        int x_{};
        int y_{};
        std::map<std::string, std::string> properties_;
    };

    struct ObjectGroup
    {
        std::string name_{};
        std::vector<Object> objects_;
    };

    std::vector<ObjectGroup> objectGroups_;
};

}  // namespace Tile

}  // namespace FA
