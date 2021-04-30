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

namespace FA {

namespace Tile {

TileMapReader::TileMapReader(const std::string& fileName)
    : fileName_(fileName)
{}

TileMapReader::~TileMapReader() = default;

void TileMapReader::Load(TextureManager& textureManager)
{
    LOG_INFO("Parse ", fileName_);
    TmxParser tmxParser(fileName_);
    
    if (tmxParser.Load()) {
        ReadMapProperties(tmxParser);
        ReadTileSets(tmxParser, textureManager);
        ReadLayers(tmxParser);
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
        TsxParser tsxParser("assets/map/tileset.tsx");
        // TsxParser tsxParser(parsedSet.source_);
        if (tsxParser.Load()) {
            auto firstGid = parsedSet.firstGid_;
            TileMapData::TileSet set;
            set.tileWidth_ = tsxParser.tileSet_.tileWidth_;
            set.tileHeight_ = tsxParser.tileSet_.tileHeight_;
            set.columns_ = tsxParser.tileSet_.columns_;
            set.texture_ = textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/environment/tileset.png");
            // set.texture_ = textureManager.GetTexture(tsxParser.image_.source_);
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
        layer.id_ = parsedLayer.id_;
        layer.tileIds_ = parsedLayer.tileIds_;
        tileMapData_.layers_.push_back(layer);
    }
}

}  // namespace Tile

}  // namespace FA
