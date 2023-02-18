/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "SfmlFwd.h"
#include "TileMap.h"

namespace FA {

namespace World {

class LevelCreator
{
public:
    void AddBackground(const std::vector<TileMap::TileData> &layer);
    void CreateBackground(const sf::Vector2u &size, sf::RenderTexture &texture) const;

    std::vector<sf::Sprite> CreateFringe(const std::vector<TileMap::TileData> &layer) const;

private:
    std::vector<std::vector<TileMap::TileData>> layers_;

private:
    sf::Sprite CreateSprite(const TileMap::TileData &data) const;
};

}  // namespace World

}  // namespace FA
