/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"
#include "TileMapData.h"

namespace FA {

namespace Tile {

class TileMap
{
public:
    TileMap(const TileMapData &tileMapData);
    ~TileMap();
    void Create();
    std::vector<sf::Sprite> GetLayer(int layerId);
    sf::Vector2u GetSize() const;

private:
    struct TileInfo
    {
        const sf::Texture *texture_ = nullptr;
        sf::IntRect uvRect_;
    };

    static const unsigned int scale{2};

    TileMapData tileMapData_;
    std::map<unsigned int, std::vector<sf::Sprite>> layers_;

private:
    TileInfo GetTileInfo(int id);
};

}  // namespace Tile

}  // namespace FA
