/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "BasicTileSetFactory.h"
#include "BasicTmxParser.h"
#include "BasicTsxParser.h"
#include "GridTileSet.h"
#include "ImageTileSet.h"
#include "TileHelper.h"
#include "TmxLogging.h"

namespace FA {

namespace Tile {

struct ParsedTmx;

template <class DocumentT, class ElementT, class ErrorT>
class TileService
{
public:
    TileService(std::unique_ptr<BasicTmxParser<DocumentT, ElementT, ErrorT>> tmxParser,
                std::unique_ptr<BasicTsxParser<DocumentT, ElementT, ErrorT>> tsxParser,
                std::unique_ptr<BasicTileSetFactory> tileSetFactory)
        : tmxParser_(std::move(tmxParser))
        , tsxParser_(std::move(tsxParser))
        , tileSetFactory_(std::move(tileSetFactory))
    {}

    ~TileService() = default;

    bool Parse(const std::string &fileName)
    {
        DocumentT doc;
        auto xmlBuffer = GetFileBuffer(fileName);
        return tmxParser_->Parse(doc, xmlBuffer, parsedTmx_);
    }

    TileMapData::MapProperties ReadMapProperties()
    {
        TileMapData::MapProperties mapProperties;
        mapProperties.width_ = parsedTmx_.map_.width_;
        mapProperties.height_ = parsedTmx_.map_.height_;
        mapProperties.tileWidth_ = parsedTmx_.map_.tileWidth_;
        mapProperties.tileHeight_ = parsedTmx_.map_.tileHeight_;

        return mapProperties;
    }

    std::map<int, TileSetData, std::greater<int>> ReadTileSets(const std::string &tmxDir)
    {
        std::map<int, TileSetData, std::greater<int>> tileSets;

        if (parsedTmx_.tileSets_.empty()) {
            LOG_TMXERROR("No tilesets found");
        }
        else {
            for (const auto &parsedSet : parsedTmx_.tileSets_) {
                auto tsxFilePath = GetFilePath(tmxDir, parsedSet.tsxSource_);
                auto tsxDir = GetHead(tsxFilePath);
                DocumentT doc;
                ParsedTsx parsedTsx;
                auto xmlBuffer = GetFileBuffer(tsxFilePath);

                if (tsxParser_->Parse(doc, xmlBuffer, parsedTsx)) {
                    auto set =
                        tileSetFactory_->Create(tsxDir, parsedTsx.tiles_, parsedTsx.tileSet_, parsedTsx.image_.source_);
                    auto firstGid = parsedSet.firstGid_;
                    auto tileSetData = set->GenerateTileData();
                    tileSets[firstGid] = tileSetData;
                }
                else {
                    LOG_TMXERROR("Can not load: ", parsedSet.tsxSource_);
                }
            }
        }

        return tileSets;
    }

    std::vector<TileMapData::Layer> ReadLayers()
    {
        std::vector<TileMapData::Layer> layers;

        for (const auto &parsedLayer : parsedTmx_.layers_) {
            TileMapData::Layer layer;
            layer.name_ = parsedLayer.name_;
            auto tileIds = ParseData(parsedLayer.data_);
            layer.tileIds_ = tileIds;
            layers.push_back(layer);
        }

        return layers;
    }

    std::vector<TileMapData::ObjectGroup> ReadObjectGroups()
    {
        std::vector<TileMapData::ObjectGroup> objectGroups;

        for (const auto &parsedObjectGroup : parsedTmx_.objectGroups_) {
            TileMapData::ObjectGroup group;
            group.name_ = parsedObjectGroup.name_;
            for (const auto &parsedObject : parsedObjectGroup.objects_) {
                TileMapData::Object object;
                object.typeStr_ = parsedObject.type_;
                object.x_ = parsedObject.x_;
                object.y_ = parsedObject.y_;
                for (const auto &parsedProperty : parsedObject.properties_) {
                    auto key = parsedProperty.first;
                    auto value = parsedProperty.second;
                    object.properties_[key] = value;
                }
                group.objects_.push_back(object);
            }
            objectGroups.push_back(group);
        }

        return objectGroups;
    }

private:
    std::unique_ptr<BasicTmxParser<DocumentT, ElementT, ErrorT>> tmxParser_;
    std::unique_ptr<BasicTsxParser<DocumentT, ElementT, ErrorT>> tsxParser_;
    std::unique_ptr<BasicTileSetFactory> tileSetFactory_;

    ParsedTmx parsedTmx_;

private:
    std::vector<int> ParseData(const std::string &dataStr) const
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
};

}  // namespace Tile

}  // namespace FA
