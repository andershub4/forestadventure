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

    struct Image
    {
        int width_{};
        int height_{};
        std::string textureFilePath_;
    };

    struct Animation
    {
        struct Frame
        {
            int tileId_{};
            int duration_{};
        };
        std::vector<Frame> frames_;
    };

    struct Tile
    {
        int id_{};
        Image image_;
        Animation animation_;
    };
    
    struct TileSet
    {
        struct Dimensions
        {
            int tileWidth_{};
            int tileHeight_{};
            int columns_{};
            int tileCount_{};
        };
        Dimensions dimensions_;
        Image image_{};
        std::vector<Tile> tiles_;
        int firstGid_{};
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
        std::map<std::string, std::string> properties_;
    };

    struct ObjectGroup
    {
        std::string name_{};
        std::vector<Object> objects_;
    };

    MapProperties mapProperties_;
    std::vector<TileSet> tileSets_;
    std::vector<Layer> layers_;
    std::vector<ObjectGroup> objectGroups_;
};

}  // namespace Tile

}  // namespace FA
