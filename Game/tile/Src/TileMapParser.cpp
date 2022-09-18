/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMapParser.h"

#include <fstream>

#include <tinyxml2/tinyxml2.h>

#include "Folder.h"
#include "GridTileSet.h"
#include "ImageTileSet.h"
#include "ParseHelper.h"
#include "TileHelper.h"
#include "TmxLogging.h"
#include "TmxParser.h"
#include "TsxParser.h"

namespace FA {

namespace Tile {

namespace {

std::unique_ptr<BasicTileSet> CreateTileSet(const std::string tsxDir, const ParsedTsx& parsedTsx)
{
    auto tiles = parsedTsx.tiles_;
    std::unique_ptr<BasicTileSet> s = nullptr;

    if (!tiles.empty()) {
        s = std::make_unique<ImageTileSet>(tsxDir, tiles);
    }
    else {
        GridTileSet::Dimensions dim;
        dim.tileWidth_ = parsedTsx.tileSet_.tileWidth_;
        dim.tileHeight_ = parsedTsx.tileSet_.tileHeight_;
        dim.columns_ = parsedTsx.tileSet_.columns_;
        dim.tileCount_ = parsedTsx.tileSet_.tileCount_;
        s = std::make_unique<GridTileSet>(tsxDir, parsedTsx.image_.source_, dim);
    }

    return s;
}

}  // namespace

TileMapParser::TileMapParser() = default;

TileMapParser::~TileMapParser() = default;

TileMapData TileMapParser::Run(const std::string& fileName)
{
    LOG_TMXINFO("Parse ", fileName);
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
        LOG_TMXERROR("Could not load ", fileName);
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
        LOG_TMXERROR("No tilesets found");
    }
    else {
        for (const auto& parsedSet : tmxParser.tileSets_) {
            auto tsxFilePath = GetFilePath(tmxDir, parsedSet.tsxSource_);
            auto tsxDir = GetHead(tsxFilePath);
            tinyxml2::XMLDocument doc;
            ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError> helper;
            TsxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError> tsxParser(helper);
            ParsedTsx parsedTsx;
            auto xmlBuffer = GetXmlBuffer(tsxFilePath);

            if (tsxParser.Parse(xmlBuffer, &doc, parsedTsx)) {
                auto set = CreateTileSet(tsxDir, parsedTsx);
                auto firstGid = parsedSet.firstGid_;
                auto tileSetData = set->CreateTileSetData();
                tileMapData_.tileSets_[firstGid] = tileSetData;
            }
            else {
                LOG_TMXERROR("Can not load: ", parsedSet.tsxSource_);
            }
        }
    }
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

std::string TileMapParser::GetXmlBuffer(const std::string& fileName) const
{
    std::ifstream ifd(fileName, std::ios::binary | std::ios::ate);
    if (ifd.good()) {
        auto size = static_cast<unsigned long>(ifd.tellg());
        ifd.seekg(0, std::ios::beg);
        std::vector<char> buffer;
        buffer.resize(size);
        ifd.read(buffer.data(), size);
        std::string xmlBuffer(buffer.begin(), buffer.end());
        return xmlBuffer;
    }

    return {};
}

}  // namespace Tile

}  // namespace FA
