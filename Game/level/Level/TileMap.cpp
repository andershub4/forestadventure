/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMap.h"

#include "Logging.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"
#include "TileMapData.h"
#include "TileMapParser.h"

namespace FA {

namespace Tile {

TileMap::TileMap(Shared::SheetManager& sheetManager)
    : sheetManager_(sheetManager)
{
    tileMapParser_ = std::make_unique<TileMapParser>();
}

TileMap::~TileMap() = default;

void TileMap::Load(const std::string& fileName)
{
    tileMapData_ = std::make_unique<TileMapData>(tileMapParser_->Run(fileName));
    LoadTileSets();
}

void TileMap::Setup()
{
    LOG_INFO("Setup tile map");
    SetupLayers();
    SetupObjectGroups();
}

void TileMap::LoadTileSets()
{
    for (auto& entry : tileMapData_->tileSets_) {
        auto images = entry.second.images_;
        for (const auto& image : images) {
            sheetManager_.LoadSheet(image.path_, image.path_, sf::Vector2u(image.nCols_, image.nRows_));
        }
    }
}

void TileMap::SetupLayers()
{
    auto nCols = tileMapData_->mapProperties_.width_;
    auto tileWidth = tileMapData_->mapProperties_.tileWidth_;
    auto tileHeight = tileMapData_->mapProperties_.tileHeight_;

    for (const auto& layer : tileMapData_->layers_) {
        int inx = 0;
        auto layerName = layer.name_;
        for (auto it = layer.tileIds_.begin(); layer.tileIds_.end() != it; ++it, ++inx) {
            auto tileId = *it;
            if (tileId == 0) continue;
            auto frameData = GetFrameData(tileId);
            auto frame = frameData.frame_;
            auto frames = frameData.frames_;
            TileMap::TileData tileData;
            unsigned int x = (inx % nCols) * tileWidth;
            unsigned int y = (inx / nCols) * tileHeight;

            if (!frames.empty()) {
                auto first = frames.at(0);
                if (first.height_ > tileHeight) {
                    y += tileHeight;
                    y -= first.height_;
                }
            }

            tileData.x_ = x;
            tileData.y_ = y;

            if (!frames.empty()) {
                std::vector<Shared::Frame> outFrames;
                for (auto f : frames) {
                    Shared::ImageData data{f.texturePath_, {f.column_, f.row_}};
                    auto frame = sheetManager_.MakeFrame(data);
                    outFrames.push_back(frame);
                }

                tileData.graphic_.animation_ = outFrames;
            }

            Shared::ImageData data{frame.texturePath_, {frame.column_, frame.row_}};
            tileData.graphic_.image_ = sheetManager_.MakeFrame(data);

            layers_[layerName].push_back(tileData);
        }
    }
}

void TileMap::SetupObjectGroups()
{
    for (const auto& group : tileMapData_->objectGroups_) {
        auto groupName = group.name_;
        std::vector<TileMap::ObjectData> objectDatas;
        for (const auto& object : group.objects_) {
            TileMap::ObjectData objectData;
            objectData.x_ = object.x_;
            objectData.y_ = object.y_;
            objectData.typeStr_ = object.typeStr_;
            objectData.properties_ = object.properties_;
            objectDatas.push_back(objectData);
        }
        objectGroups_[groupName] = objectDatas;
    }
}

const std::vector<TileMap::TileData>& TileMap::GetLayer(const std::string& name) const
{
    return layers_.at(name);
}

const std::vector<TileMap::ObjectData> TileMap::GetObjectGroup(const std::string& name) const
{
    return objectGroups_.at(name);
}

sf::Vector2u TileMap::GetSize() const
{
    auto nCols = tileMapData_->mapProperties_.width_;
    auto nRows = tileMapData_->mapProperties_.height_;
    auto tileWidth = tileMapData_->mapProperties_.tileWidth_;
    auto tileHeight = tileMapData_->mapProperties_.tileHeight_;
    auto size = sf::Vector2i(nCols * tileWidth, nRows * tileHeight);

    return static_cast<sf::Vector2u>(size);
}

FrameData TileMap::GetFrameData(int id)
{
    auto it = tileMapData_->tileSets_.lower_bound(id);

    if (it != tileMapData_->tileSets_.end()) {
        auto firstGid = it->first;
        return it->second.lookupTable_[id - firstGid];
    }
    else {
        LOG_ERROR("Id %u not found", id);
        return {};
    }
}

}  // namespace Tile

}  // namespace FA
