/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMap.h"

namespace FA {

namespace Tile {

TileMap::TileMap(const TileMapData& tileMapData)
    : tileMapData_(tileMapData)
{}

TileMap::~TileMap() = default;

void TileMap::Create()
{
    auto nCols = tileMapData_.mapProperties_.width_;
    auto nRows = tileMapData_.mapProperties_.height_;
    auto tileWidth = tileMapData_.mapProperties_.tileWidth_;
    auto tileHeight = tileMapData_.mapProperties_.tileHeight_;

    for (const auto& layer : tileMapData_.layers_) {
        int inx = 0;
        auto layerName = layer.name_;
        for (auto it = layer.tileIds_.begin(); layer.tileIds_.end() != it; ++it, ++inx) {
            auto tileId = *it;
            if (tileId == 0) continue;
            float x = static_cast<float>((inx % nCols) * tileWidth * scale);
            float y = static_cast<float>((inx / nCols) * tileHeight * scale);
            auto tileInfo = GetTileInfo(tileId);

            if (tileInfo.texture_ != nullptr) {
                sf::Sprite tile;
                tile.setTexture(*tileInfo.texture_);
                tile.setTextureRect(tileInfo.uvRect_);
                tile.setPosition(x, y);
                tile.setScale(scale, scale);
                layers_[layerName].push_back(tile);
            }
        }
    }
}

const std::vector<sf::Sprite>& TileMap::GetLayer(const std::string& name)
{
    return layers_.at(name);
}

sf::Vector2u TileMap::GetSize() const
{
    auto nCols = tileMapData_.mapProperties_.width_;
    auto nRows = tileMapData_.mapProperties_.height_;
    auto tileWidth = tileMapData_.mapProperties_.tileWidth_;
    auto tileHeight = tileMapData_.mapProperties_.tileHeight_;

    return {nCols * tileWidth * scale, nRows * tileHeight * scale};
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

}  // namespace Tile

}  // namespace FA
