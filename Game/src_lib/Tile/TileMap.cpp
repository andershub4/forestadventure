/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMap.h"

#include "FrameData.h"
#include "GridTileSet.h"
#include "ImageTileSet.h"
#include "Logging.h"
#include "Resource/Image.h"

namespace FA {

namespace Tile {

TileMap::TileMap(SheetManager& sheetManager, unsigned int scale)
    : sheetManager_(sheetManager)
    , scale_(scale)
{}

TileMap::~TileMap() = default;

void TileMap::Create(const TileMapData& tileMapData)
{
    LOG_INFO("Create tile map");
    tileMapData_ = tileMapData;
    CreateTileSets();
    CreateLayers();
    CreateObjectGroups();
}

std::unique_ptr<BasicTileSet> TileMap::CreateTileSet(const TileMapData::TileSet& tileSet) const
{
    if (!tileSet.tiles_.empty()) {
        return std::make_unique<ImageTileSet>(tileSet, sheetManager_);
    }
    else {
        return std::make_unique<GridTileSet>(tileSet, sheetManager_);
    }
}

void TileMap::CreateTileSets()
{
    for (const auto& tileSet : tileMapData_.tileSets_) {
        auto s = CreateTileSet(tileSet);
        s->Load();
        auto firstGid = tileSet.firstGid_;
        tileSets_[firstGid] = std::move(s);
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
            auto frameData = GetFrameData(tileId);
            Image image(frameData.frame_, 0.0);

            sf::Sprite tile;
            image.ApplyTo(tile);
            tile.setPosition(x, y);
            tile.setScale(static_cast<float>(scale_), static_cast<float>(scale_));
            layers_[layerName].push_back(tile);
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
            objectData.scale_ = scale_;
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

FrameData TileMap::GetFrameData(int id)
{
    auto it = tileSets_.lower_bound(id);

    if (it != tileSets_.end()) {
        auto firstGid = it->first;
        return it->second->GetFrameData(id - firstGid);
    }
    else {
        LOG_ERROR("Id ", id, "not found");
        return {};
    }
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
