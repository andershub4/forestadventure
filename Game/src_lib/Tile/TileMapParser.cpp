/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMapParser.h"

#include "Folder.h"
#include "Logging.h"
#include "TmxParser.h"
#include "TsxParser.h"

namespace FA {

namespace Tile {

TileMapParser::TileMapParser() = default;

TileMapParser::~TileMapParser() = default;

TileMapData TileMapParser::Run(const std::string& fileName)
{
    LOG_INFO("Parse ", fileName);
    LOG_TMXINFO("Start parse fileName ", fileName);
    TmxParser tmxParser;

    if (tmxParser.Parse(fileName)) {
        ReadMapProperties(tmxParser);
        auto tmxDir = GetHead(fileName);
        ReadTileSets(tmxParser, tmxDir);
        ReadLayers(tmxParser);
        ReadObjectGroups(tmxParser);
    }
    else {
        LOG_ERROR("Could not load ", fileName);
    }

    LOG_TMXINFO("End parse fileName ", fileName);

    return tileMapData_;
}

void TileMapParser::ReadMapProperties(const TmxParser& tmxParser)
{
    tileMapData_.mapProperties_.width_ = tmxParser.map_.width_;
    tileMapData_.mapProperties_.height_ = tmxParser.map_.height_;
    tileMapData_.mapProperties_.tileWidth_ = tmxParser.map_.tileWidth_;
    tileMapData_.mapProperties_.tileHeight_ = tmxParser.map_.tileHeight_;
}

void TileMapParser::ReadTileSets(const TmxParser& tmxParser, const std::string& tmxDir)
{
    if (tmxParser.tileSets_.empty()) {
        LOG_ERROR("No tilesets found");
    }
    else {
        for (const auto& parsedSet : tmxParser.tileSets_) {
            auto tsxFilePath = GetFilePath(tmxDir, parsedSet.tsxSource_);
            auto tsxDir = GetHead(tsxFilePath);
            TsxParser tsxParser;
            if (tsxParser.Parse(tsxFilePath)) {
                TileMapData::TileSet set;
                set.firstGid_ = parsedSet.firstGid_;
                set.dimensions_.tileWidth_ = tsxParser.tileSet_.tileWidth_;
                set.dimensions_.tileHeight_ = tsxParser.tileSet_.tileHeight_;
                set.dimensions_.columns_ = tsxParser.tileSet_.columns_;
                set.dimensions_.tileCount_ = tsxParser.tileSet_.tileCount_;
                set.image_ = GetImage(tsxDir, tsxParser);
                set.tiles_ = GetTiles(tsxDir, tsxParser);
                tileMapData_.tileSets_.push_back(set);
            }
            else {
                LOG_ERROR("Can not load: ", parsedSet.tsxSource_);
            }
        }
    }
}

TileMapData::Image TileMapParser::GetImage(const std::string& tsxDir, const TsxParser& tsxParser) const
{
    auto textureFilePath = GetFilePath(tsxDir, tsxParser.image_.source_);
    return {tsxParser.image_.width_, tsxParser.image_.height_, textureFilePath};
}

std::vector<TileMapData::Tile> TileMapParser::GetTiles(const std::string& tsxDir, const TsxParser& tsxParser) const
{
    std::vector<TileMapData::Tile> tiles;
    auto parsedTiles = tsxParser.tiles_;
    for (const auto& parsedTile : parsedTiles) {
        TileMapData::Tile tile;
        tile.image_.textureFilePath_ = GetFilePath(tsxDir, parsedTile.image_.source_);
        tile.image_.width_ = parsedTile.image_.width_;
        tile.image_.height_ = parsedTile.image_.height_;
        tile.id_ = parsedTile.id_;
        auto animation = parsedTile.animation_;
        for (const auto& frame : animation.frames_) {
            TileMapData::Animation::Frame f;
            f.tileId_ = frame.tiledId_;
            f.duration_ = frame.duration_;
            tile.animation_.frames_.push_back(f);
        }
        tiles.push_back(tile);
    }

    return tiles;
}

void TileMapParser::ReadLayers(const TmxParser& tmxParser)
{
    for (const auto& parsedLayer : tmxParser.layers_) {
        TileMapData::Layer layer;
        layer.name_ = parsedLayer.name_;
        layer.tileIds_ = parsedLayer.tileIds_;
        tileMapData_.layers_.push_back(layer);
    }
}

void TileMapParser::ReadObjectGroups(const TmxParser& tmxParser)
{
    for (const auto& parsedObjectGroup : tmxParser.objectGroups_) {
        TileMapData::ObjectGroup group;
        group.name_ = parsedObjectGroup.name_;
        for (const auto& parsedObject : parsedObjectGroup.objects_) {
            TileMapData::Object object;
            object.typeStr_ = parsedObject.type_;
            object.x_ = parsedObject.x_;
            object.y_ = parsedObject.y_;
            for (const auto& parsedProperty : parsedObject.properties_) {
                auto key = parsedProperty.first;
                auto value = parsedProperty.second;
                object.properties_[key] = value;
            }
            group.objects_.push_back(object);
        }
        tileMapData_.objectGroups_.push_back(group);
    }
}

std::string TileMapParser::GetFilePath(const std::string& baseDir, const std::string& source) const
{
    auto head = baseDir;
    auto tail = source;

    const std::string moveBackMatch = "../";
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
