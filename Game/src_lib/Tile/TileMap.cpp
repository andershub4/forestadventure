/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMap.h"

#include <unordered_map>

#include "Constant/Screen.h"
#include "Misc/Random.h"

namespace FA {

namespace Tile {

const std::unordered_map<TileMap::Id, sf::IntRect> mapLookup = {{TileMap::Id::BasicGround, {208, 288, 15, 15}},
                                                                {TileMap::Id::Ground1, {240, 400, 15, 15}},
                                                                {TileMap::Id::GroundPlant, {240, 368, 15, 15}},
                                                                {TileMap::Id::GreenPlant, {208, 400, 15, 15}}};

TileMap::TileMap()
{
    renderTexture_.create(nCols * tileSize * scale, nRows * tileSize * scale);
}

TileMap::~TileMap() = default;

void TileMap::Load(const sf::Texture* texture)
{
    float x = 0;
    float y = 0;
    sf::Sprite tile(*texture);

    for (unsigned int row = 0; row < nRows; row++) {
        x = 0;
        for (unsigned int col = 0; col < nCols; col++) {
            auto id = RandomizeId();
            auto it = mapLookup.find(id);

            if (it != mapLookup.end()) {
                tile.setTextureRect(it->second);
                tile.setPosition(x, y);
                tile.setScale(scale, scale);
                renderTexture_.draw(tile);
            }
            x += (tileSize * scale);
        }
        y += (tileSize * scale);
    }

    renderTexture_.display();
    tileMap_.setTexture(renderTexture_.getTexture());
}

void TileMap::Draw(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(tileMap_);
}

sf::Vector2u TileMap::GetSize() const
{
    return renderTexture_.getSize();
}

TileMap::Id TileMap::RandomizeId() const
{
    auto r = RandomizeRange(0, 100);
    TileMap::Id id;
    if (r < 4) {
        id = TileMap::Id::GreenPlant;
    }
    else if (r >= 4 && r < 15) {
        id = TileMap::Id::Ground1;
    }
    else if (r >= 15 && r < 20) {
        id = TileMap::Id::GroundPlant;
    }
    else {
        id = TileMap::Id::BasicGround;
    }

    return id;
}

}  // namespace Tile

}  // namespace FA
