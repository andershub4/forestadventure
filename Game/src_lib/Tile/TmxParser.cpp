/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TmxParser.h"

#include "tinyxml2/tinyxml2.h"

#include "Utils/Logger.h"

namespace FA {

namespace Tile {

TmxParser::TmxParser(const std::string& fileName)
    : fileName_(fileName)
{}

TmxParser::~TmxParser() = default;

bool TmxParser::Load()
{
    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(fileName_.c_str());

    tinyxml2::XMLElement* map = xmlDoc.FirstChildElement("map");
    ParseMapElement(map);

    return true;
}

void TmxParser::ParseMapElement(tinyxml2::XMLElement* mapElement)
{
    map_.renderOrder_ = mapElement->Attribute("renderorder");
    mapElement->QueryAttribute("width", &map_.width_);
    mapElement->QueryAttribute("height", &map_.height_);
    mapElement->QueryAttribute("tilewidth", &map_.tileWidth_);
    mapElement->QueryAttribute("tileheight", &map_.tileHeight_);
    LOG_INFO("renderOrder: ", map_.renderOrder_);
    LOG_INFO("width: ", map_.width_, " height: ", map_.height_);
    LOG_INFO("tileWidth: ", map_.tileWidth_, " tileHeight: ", map_.tileHeight_);

    tinyxml2::XMLElement* tileSetElement = mapElement->FirstChildElement("tileset");
    while (tileSetElement != nullptr) {
        TileSet set;
        ParseTileSetElement(tileSetElement, set);
        tileSets_.push_back(set);
        tileSetElement = tileSetElement->NextSiblingElement("tileset");
    }

    tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
    while (layerElement != nullptr) {
        Layer layer;
        ParseLayerElement(layerElement, layer);
        layers_.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }
}

void TmxParser::ParseTileSetElement(tinyxml2::XMLElement* tileSetElement, TileSet& tileSet)
{
    tileSetElement->QueryAttribute("firstgid", &tileSet.firstGid_);
    tileSet.source_ = tileSetElement->Attribute("source");
    LOG_INFO("firstGid: ", tileSet.firstGid_);
    LOG_INFO("source: ", tileSet.source_);
}

void TmxParser::ParseLayerElement(tinyxml2::XMLElement* layerElement, Layer& layer)
{
    layerElement->QueryAttribute("id", &layer.id_);
    layer.name_ = layerElement->Attribute("name");
    layerElement->QueryAttribute("width", &layer.width_);
    layerElement->QueryAttribute("height", &layer.height_);
    LOG_INFO("layer.id_: ", layer.id_);
    LOG_INFO("layer.name_: ", layer.name_);
    LOG_INFO("layer.width_: ", layer.width_);
    LOG_INFO("layer.height_: ", layer.height_);

    auto dataElement = layerElement->FirstChildElement("data");
    ParseDataElement(dataElement, layer.tileIds_);
}

void TmxParser::ParseDataElement(tinyxml2::XMLElement* dataElement, std::vector<int>& ids)
{
    std::string text = dataElement->GetText();
    std::size_t pos = 0;
    while ((pos = text.find(",")) != std::string::npos) {
        auto id = text.substr(0, pos);
        ids.push_back(std::stoi(id));
        text.erase(0, pos + 1);
    }
}

}  // namespace Tile

}  // namespace FA
