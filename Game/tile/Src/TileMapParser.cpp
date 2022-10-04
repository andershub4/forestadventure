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
    tinyxml2::XMLDocument doc;
    ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError> helper;
    TmxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError> tmxParser(doc, helper);
    ParsedTmx parsedTmx;

    if (tmxParser.Parse(fileName, parsedTmx)) {
        ReadMapProperties(parsedTmx);
        auto tmxDir = GetHead(fileName);
        ReadTileSets(parsedTmx, tmxDir);
        ReadLayers(parsedTmx);
        ReadObjectGroups(parsedTmx);
    }
    else {
        LOG_TMXERROR("Could not load ", fileName);
    }

    LOG_TMXINFO("End parse fileName ", fileName);

    return tileMapData_;
}

void TileMapParser::ReadMapProperties(const ParsedTmx& parsedTmx)
{
    tileMapData_.mapProperties_.width_ = parsedTmx.map_.width_;
    tileMapData_.mapProperties_.height_ = parsedTmx.map_.height_;
    tileMapData_.mapProperties_.tileWidth_ = parsedTmx.map_.tileWidth_;
    tileMapData_.mapProperties_.tileHeight_ = parsedTmx.map_.tileHeight_;
}

void TileMapParser::ReadTileSets(const ParsedTmx& parsedTmx, const std::string& tmxDir)
{
    if (parsedTmx.tileSets_.empty()) {
        LOG_TMXERROR("No tilesets found");
    }
    else {
        for (const auto& parsedSet : parsedTmx.tileSets_) {
            auto tsxFilePath = GetFilePath(tmxDir, parsedSet.tsxSource_);
            auto tsxDir = GetHead(tsxFilePath);
            tinyxml2::XMLDocument doc;
            ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError> helper;
            TsxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError> tsxParser(doc, helper);
            ParsedTsx parsedTsx;
            auto xmlBuffer = GetXmlBuffer(tsxFilePath);

            if (tsxParser.Parse(xmlBuffer, parsedTsx)) {
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

void TileMapParser::ReadLayers(const ParsedTmx& parsedTmx)
{
    for (const auto& parsedLayer : parsedTmx.layers_) {
        TileMapData::Layer layer;
        layer.name_ = parsedLayer.name_;
        auto tileIds = ParseData(parsedLayer.data_);
        layer.tileIds_ = tileIds;
        tileMapData_.layers_.push_back(layer);
    }
}

void TileMapParser::ReadObjectGroups(const ParsedTmx& parsedTmx)
{
    for (const auto& parsedObjectGroup : parsedTmx.objectGroups_) {
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

std::vector<int> TileMapParser::ParseData(const std::string& dataStr) const
{
    std::string text = dataStr;
    std::vector<int> ids;
    std::size_t pos = 0;
    while ((pos = text.find(",")) != std::string::npos) {
        auto id = text.substr(0, pos);
        ids.push_back(std::stoi(id));
        text.erase(0, pos + 1);
    }

    ids.push_back(std::stoi(text));

    return ids;
}

}  // namespace Tile

}  // namespace FA
