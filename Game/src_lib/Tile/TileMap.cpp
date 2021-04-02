/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMap.h"

#include "Constant/Screen.h"
#include "Enum/TileType.h"
#include "Misc/Random.h"
#include "Resource/TileSet.h"

namespace FA {

namespace Tile {

TileMap::TileMap(const TileSet& tileSet)
    : tileSet_(tileSet)
{
    mapTexture_.create(nCols * tileSize * scale, nRows * tileSize * scale);
}

TileMap::~TileMap() = default;

void TileMap::Load()
{
    DrawGround(mapTexture_);
    DrawPlants(mapTexture_);
    mapTexture_.display();
    tileMap_.setTexture(mapTexture_.getTexture());
}

void TileMap::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(tileMap_);
}

sf::Vector2u TileMap::GetSize() const
{
    return mapTexture_.getSize();
}

void TileMap::ApplyTile(TileType type, float x, float y, sf::RenderTexture &mapTexture)
{
    if (type == TileType::None) return;

    sf::Sprite tile;
    auto tileInfo = tileSet_.GetTile(type);

    if (tileInfo.texture_ != nullptr) {
        tile.setTexture(*tileInfo.texture_);
        tile.setTextureRect(tileInfo.rect_);
        tile.setPosition(x, y);
        tile.setScale(scale, scale);
        mapTexture.draw(tile);
    }
}

void TileMap::DrawGround(sf::RenderTexture& mapTexture)
{
    float x = 0;
    float y = 0;

    for (unsigned int row = 0; row < nRows; row++) {
        x = 0;
        for (unsigned int col = 0; col < nCols; col++) {
            auto type = TileType::BasicGround;
            ApplyTile(type, x, y, mapTexture_);
            x += (tileSize * scale);
        }
        y += (tileSize * scale);
    } 
}

void TileMap::DrawPlants(sf::RenderTexture& mapTexture)
{
    float x = 0;
    float y = 0;

    for (unsigned int row = 0; row < nRows; row++) {
        x = 0;
        for (unsigned int col = 0; col < nCols; col++) {
            auto type = RandomizeType();
            ApplyTile(type, x, y, mapTexture_);
            x += (tileSize * scale);
        }
        y += (tileSize * scale);
    }
}

TileType TileMap::RandomizeType() const
{
    auto r = RandomizeRange(0, 100);
    TileType t{};
    if (r < 4) {
        t = TileType::GreenPlant;
    }
    else if (r >= 4 && r < 15) {
        t = TileType::Ground1;
    }
    else if (r >= 15 && r < 20) {
        t = TileType::GroundPlant;
    }

    return t;
}

}  // namespace Tile

}  // namespace FA
