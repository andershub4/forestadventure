/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TsxParser.h"

#include "tinyxml2/tinyxml2.h"

#include "Logging.h"

namespace FA {

namespace Tile {

TsxParser::TsxParser() = default;

TsxParser::~TsxParser() = default;

bool TsxParser::Parse(const std::string& fileName)
{
    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(fileName.c_str());

    if (xmlDoc.Error()) {
        return false;
    }
    else {
        tinyxml2::XMLElement* tileSetElement = xmlDoc.FirstChildElement("tileset");
        ParseTileSetElement(tileSetElement);
        return true;
    }
}

void TsxParser::ParseTileSetElement(tinyxml2::XMLElement* tileSetElement)
{
    tileSet_.name_ = tileSetElement->Attribute("name");
    tileSetElement->QueryAttribute("tilewidth", &tileSet_.tileWidth_);
    tileSetElement->QueryAttribute("tileheight", &tileSet_.tileHeight_);
    tileSetElement->QueryAttribute("tilecount", &tileSet_.tileCount_);
    tileSetElement->QueryAttribute("columns", &tileSet_.columns_);
    LOG_TMXINFO("name: ", tileSet_.name_);
    LOG_TMXINFO("tileWidth: ", tileSet_.tileWidth_, " tileHeight: ", tileSet_.tileHeight_);
    LOG_TMXINFO("tileCount: ", tileSet_.tileCount_, " columns: ", tileSet_.columns_);

    tinyxml2::XMLElement* imageElement = tileSetElement->FirstChildElement("image");
    ParseImageElement(imageElement, image_);
}

void TsxParser::ParseImageElement(tinyxml2::XMLElement* imageElement, Image& image)
{
    image.source_ = imageElement->Attribute("source");
    imageElement->QueryAttribute("width", &image.width_);
    imageElement->QueryAttribute("height", &image.height_);
    LOG_TMXINFO("source: ", image.source_);
    LOG_TMXINFO("width: ", image.width_, " height: ", image.height_);
}

}  // namespace Tile

}  // namespace FA
