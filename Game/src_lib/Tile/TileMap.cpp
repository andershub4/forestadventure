/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMap.h"

#include "Misc/TextureManager.h"

namespace FA {

namespace Tile {

TileMap::TileMap(const TileMapData& tileMapData, TextureManager& textureManager, unsigned int scale)
    : textureManager_(textureManager)
    , tileMapData_(tileMapData)
    , scale_(scale)
{}

TileMap::~TileMap() = default;

void TileMap::Create()
{
    CreateTileSets();
    CreateLayers();
    CreateObjectGroups();
}

void TileMap::CreateTileSets()
{
    for (const auto& tileSet : tileMapData_.tileSets_) {
        TileMap::TileSet s;
        s.firstGid_ = tileSet.firstGid_;
        s.columns_ = tileSet.columns_;
        s.tileSize_ = sf::Vector2u(tileSet.tileWidth_, tileSet.tileHeight_);
        s.texture_ = textureManager_.GetTexture(tileSet.textureFilePath_);
        tileSets_.push_back(s);
    }
}

void TileMap::CreateLayers()
{
    auto nCols = tileMapData_.mapProperties_.width_;
    auto tileWidth = tileMapData_.mapProperties_.tileWidth_;
    auto tileHeight = tileMapData_.mapProperties_.tileHeight_;

    for (const auto& layer : tileMapData_.layers_) {
        int inx = 0;
        auto layerName = layer.name_;
        for (auto it = layer.tileIds_.begin(); layer.tileIds_.end() != it; ++it, ++inx) {
            auto tileId = *it;
            if (tileId == 0) continue;
            float x = static_cast<float>((inx % nCols) * tileWidth * scale_);
            float y = static_cast<float>((inx / nCols) * tileHeight * scale_);
            auto tileInfo = GetTileInfo(tileId);

            if (tileInfo.texture_ != nullptr) {
                sf::Sprite tile;
                tile.setTexture(*tileInfo.texture_);
                tile.setTextureRect(tileInfo.uvRect_);
                tile.setPosition(x, y);
                tile.setScale(static_cast<float>(scale_), static_cast<float>(scale_));
                layers_[layerName].push_back(tile);
            }
        }
    }
}

void TileMap::CreateObjectGroups()
{
    for (const auto& group : tileMapData_.objectGroups_) {
        auto groupName = group.name_;
        std::vector<TileMap::ObjectData> objectDatas;
        for (const auto& object : group.objects_) {
            TileMap::ObjectData objectData;
            objectData.position_ = {object.x_ * scale_, object.y_ * scale_};
            objectData.type_ = ObjTypeStrToEnum(object.typeStr_);
            objectData.faceDir_ = FaceDirStrToEnum(object.properties_.at("FaceDirection"));
            objectDatas.push_back(objectData);
        }
        objectGroups_[groupName] = objectDatas;
    }
}

const std::vector<sf::Sprite>& TileMap::GetLayer(const std::string& name)
{
    return layers_.at(name);
}

const std::vector<TileMap::ObjectData> TileMap::GetObjectGroup(const std::string& name)
{
    return objectGroups_.at(name);
}

sf::Vector2u TileMap::GetSize() const
{
    auto nCols = tileMapData_.mapProperties_.width_;
    auto nRows = tileMapData_.mapProperties_.height_;
    auto tileWidth = tileMapData_.mapProperties_.tileWidth_;
    auto tileHeight = tileMapData_.mapProperties_.tileHeight_;

    return {nCols * tileWidth * scale_, nRows * tileHeight * scale_};
}

TileMap::TileInfo TileMap::GetTileInfo(int id)
{
    auto it = tileSets_.begin();
    id--;

    auto texture = it->texture_;
    auto column = id % it->columns_;
    auto row = id / it->columns_;
    auto u = column * it->tileSize_.x;
    auto v = row * it->tileSize_.y;
    sf::IntRect uvRect = sf::IntRect(u, v, it->tileSize_.x, it->tileSize_.y);

    return {texture, uvRect};
}

EntityType TileMap::ObjTypeStrToEnum(const std::string& typeStr) const
{
    auto result = EntityType::Unknown;

    if (typeStr == "Mole") {
        result = EntityType::Mole;
    }
    else if (typeStr == "Player") {
        result = EntityType::Player;
    }

    return result;
}

FaceDirection TileMap::FaceDirStrToEnum(const std::string& faceDirStr) const
{
    auto result = FaceDirection::Down;

    if (faceDirStr == "Up") {
        result = FaceDirection::Up;
    }
    else if (faceDirStr == "Down") {
        result = FaceDirection::Down;
    }
    else if (faceDirStr == "Right") {
        result = FaceDirection::Right;
    }
    else if (faceDirStr == "Left") {
        result = FaceDirection::Left;
    }

    return result;
}

}  // namespace Tile

}  // namespace FA
