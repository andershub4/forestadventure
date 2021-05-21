/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMapReader.h"

#include "Misc/TextureManager.h"
#include "TmxParser.h"
#include "TsxParser.h"
#include "Utils/Logger.h"
#include "Utils/Path.h"

namespace FA {

namespace Tile {

TileMapReader::TileMapReader(const std::string& fileName, TextureManager& textureManager)
    : fileName_(fileName)
    , textureManager_(textureManager)
{}

TileMapReader::~TileMapReader() = default;

void TileMapReader::Load()
{
    LOG_INFO("Parse ", fileName_);
    TmxParser tmxParser(fileName_);

    if (tmxParser.Load()) {
        ReadMapProperties(tmxParser);
        ReadTileSets(tmxParser, textureManager_);
        ReadLayers(tmxParser);
        ReadObjectGroups(tmxParser);
    }
    else {
        LOG_ERROR("Can not load: ", fileName_);
    }
}

void TileMapReader::ReadMapProperties(const TmxParser& tmxParser)
{
    tileMapData_.mapProperties_.width_ = tmxParser.map_.width_;
    tileMapData_.mapProperties_.height_ = tmxParser.map_.height_;
    tileMapData_.mapProperties_.tileWidth_ = tmxParser.map_.tileWidth_;
    tileMapData_.mapProperties_.tileHeight_ = tmxParser.map_.tileHeight_;
}

void TileMapReader::ReadTileSets(const TmxParser& tmxParser, TextureManager& textureManager)
{
    if (tmxParser.tileSets_.empty()) {
        LOG_ERROR("No tilesets found");
    }
    else {
        if (tmxParser.tileSets_.size() > 1) {
            LOG_ERROR("Only 1 tileset is currently supported, reading first one");
        }

        auto parsedSet = tmxParser.tileSets_[0];
        auto tmxDir = GetHead(fileName_);
        auto tsxFilePath = GetFilePath(tmxDir, parsedSet.source_);
        TsxParser tsxParser(tsxFilePath);
        if (tsxParser.Load()) {
            auto firstGid = parsedSet.firstGid_;
            TileMapData::TileSet set;
            set.tileWidth_ = tsxParser.tileSet_.tileWidth_;
            set.tileHeight_ = tsxParser.tileSet_.tileHeight_;
            set.columns_ = tsxParser.tileSet_.columns_;
            auto tsxDir = GetHead(tsxFilePath);
            auto textureFilePath = GetFilePath(tsxDir, tsxParser.image_.source_);
            set.texture_ = textureManager.GetTexture(textureFilePath);
            tileMapData_.tileSets_[firstGid] = set;
        }
        else {
            LOG_ERROR("Can not load: ", parsedSet.source_);
        }
    }
}

void TileMapReader::ReadLayers(const TmxParser& tmxParser)
{
    for (auto& parsedLayer : tmxParser.layers_) {
        TileMapData::Layer layer;
        layer.name_ = parsedLayer.name_;
        layer.tileIds_ = parsedLayer.tileIds_;
        tileMapData_.layers_.push_back(layer);
    }
}

void TileMapReader::ReadObjectGroups(const TmxParser& tmxParser)
{
    for (auto& parsedObjectGroup : tmxParser.objectGroups_) {
        TileMapData::ObjectGroup group;
        group.name_ = parsedObjectGroup.name_;
        for (auto& parsedObject : parsedObjectGroup.objects_) {
            TileMapData::Object object;
            object.typeStr_ = parsedObject.type_;
            object.position_ = sf::Vector2u(parsedObject.x_, parsedObject.y_);
            for (auto& parsedProperty : parsedObject.properties_) {
                auto key = parsedProperty.first;
                auto value = parsedProperty.second;
                object.properties_[key] = value;
            }
            group.objects_.push_back(object);
        }
        tileMapData_.objectGroups_.push_back(group);
    }
}

std::string TileMapReader::GetFilePath(const std::string& baseDir, const std::string& source) const
{
    auto head = baseDir;
    auto tail = source;

    std::string moveBackMatch = "../";
    auto index = tail.find(moveBackMatch);
    while (index != std::string::npos) {
        head = GetHead(head);
        tail = tail.substr(index + moveBackMatch.size());
        index = tail.find(moveBackMatch);
    }

    return head + '/' + tail;
}

}  // namespace Tile

}  // namespace FA
