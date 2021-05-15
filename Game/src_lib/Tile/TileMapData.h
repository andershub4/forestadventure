/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <vector>

#include "Fwd/SfmlFwd.h"

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
        const sf::Texture* texture_ = nullptr;
    };

    std::map<int, TileSet> tileSets_;

    struct Layer
    {
        std::string name_{};
        std::vector<int> tileIds_;
    };

    std::vector<Layer> layers_;
};

}  // namespace Tile

}  // namespace FA
