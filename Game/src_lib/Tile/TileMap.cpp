/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMap.h"

#include "TileMapData.h"
#include "Utils/Logger.h"

namespace FA {

namespace Tile {

TileMap::TileMap(const TileMapData& tileMapData)
    : tileMapData_(tileMapData)
{}

TileMap::~TileMap() = default;

void TileMap::Load()
{
    auto nCols = tileMapData_.mapProperties_.width_;
    auto nRows = tileMapData_.mapProperties_.height_;
    auto tileWidth = tileMapData_.mapProperties_.tileWidth_;
    auto tileHeight = tileMapData_.mapProperties_.tileHeight_;

    mapTexture_.create(nCols * tileWidth * scale, nRows * tileHeight * scale);

    for (const auto& layer : tileMapData_.layers_) {
        int inx = 0;
        for (const auto& tileId : layer.tileIds_) {
            auto x = (inx % nCols) * tileWidth * scale;
            auto y = (inx / nCols) * tileHeight * scale;
            auto tileInfo = GetTileInfo(tileId);
            ApplyTile(tileInfo, sf::Vector2i(x, y), mapTexture_);
            inx++;
        }
    }
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

TileMap::TileInfo TileMap::GetTileInfo(int id)
{
    auto it = tileMapData_.tileSets_.begin();
    id--;

    auto texture = it->second.texture_;
    auto column = id % it->second.columns_;
    auto row = id / it->second.columns_;
    auto u = column * it->second.tileWidth_;
    auto v = row * it->second.tileHeight_;
    sf::IntRect uvRect = {u, v, it->second.tileWidth_, it->second.tileHeight_};

    return {texture, uvRect};
}

void TileMap::ApplyTile(const TileMap::TileInfo& tileInfo, const sf::Vector2i& position, sf::RenderTexture& mapTexture)
{
    sf::Sprite tile;

    if (tileInfo.texture_ != nullptr) {
        tile.setTexture(*tileInfo.texture_);
        tile.setTextureRect(tileInfo.uvRect_);
        tile.setPosition(static_cast<sf::Vector2f>(position));
        tile.setScale(scale, scale);
        mapTexture.draw(tile);
    }
}

}  // namespace Tile

}  // namespace FA
