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
    renderTexture_.create(nCols * tileSize * scale, nRows * tileSize * scale);
}

TileMap::~TileMap() = default;

void TileMap::Load()
{
    float x = 0;
    float y = 0;
    sf::Sprite tile;

    for (unsigned int row = 0; row < nRows; row++) {
        x = 0;
        for (unsigned int col = 0; col < nCols; col++) {
            auto type = RandomizeType();
            auto tileInfo = tileSet_.GetTile(type);

            if (tileInfo.texture_ != nullptr) {
                tile.setTexture(*tileInfo.texture_);
                tile.setTextureRect(tileInfo.rect_);
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

void TileMap::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(tileMap_);
}

sf::Vector2u TileMap::GetSize() const
{
    return renderTexture_.getSize();
}

TileType TileMap::RandomizeType() const
{
    auto r = RandomizeRange(0, 100);
    TileType t;
    if (r < 4) {
        t = TileType::GreenPlant;
    }
    else if (r >= 4 && r < 15) {
        t = TileType::Ground1;
    }
    else if (r >= 15 && r < 20) {
        t = TileType::GroundPlant;
    }
    else {
        t = TileType::BasicGround;
    }

    return t;
}

}  // namespace Tile

}  // namespace FA
