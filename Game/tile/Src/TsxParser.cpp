/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TsxParser.h"

#include "tinyxml2/tinyxml2.h"

#include "TmxLogging.h"

namespace FA {

namespace Tile {

TsxParser::TsxParser(std::unique_ptr<tinyxml2::XMLDocument> xmlDocument)
    : xmlDocument_(std::move(xmlDocument))
{}

TsxParser::~TsxParser() = default;

bool TsxParser::Parse(const std::string& fileName)
{
    xmlDocument_->LoadFile(fileName.c_str());

    if (xmlDocument_->Error()) {
        return false;
    }
    else {
        tinyxml2::XMLElement* tileSetElement = xmlDocument_->FirstChildElement("tileset");
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

    tinyxml2::XMLElement* tileElement = tileSetElement->FirstChildElement("tile");
    if (tileElement) {  // Collection of images
        while (tileElement != nullptr) {
            Tile tile;
            ParseTileElement(tileElement, tile);
            tiles_.push_back(tile);
            tileElement = tileElement->NextSiblingElement("tile");
        }
    }
    else {  // Based on grid image
        tinyxml2::XMLElement* imageElement = tileSetElement->FirstChildElement("image");
        ParseImageElement(imageElement, image_);
    }
}

void TsxParser::ParseTileElement(tinyxml2::XMLElement* tileElement, Tile& tile)
{
    tileElement->QueryAttribute("id", &tile.id_);
    tinyxml2::XMLElement* imageElement = tileElement->FirstChildElement("image");
    ParseImageElement(imageElement, tile.image_);
    tinyxml2::XMLElement* animationElement = tileElement->FirstChildElement("animation");

    if (animationElement) {
        tinyxml2::XMLElement* frameElement = animationElement->FirstChildElement("frame");

        while (frameElement != nullptr) {
            ParsedFrame frame;
            ParseFrameElement(frameElement, frame);
            tile.frames_.push_back(frame);
            frameElement = frameElement->NextSiblingElement("frame");
        }
    }
}

void TsxParser::ParseFrameElement(tinyxml2::XMLElement* frameElement, ParsedFrame& frame)
{
    frameElement->QueryAttribute("tileid", &frame.tiledId_);
    frameElement->QueryAttribute("duration", &frame.duration_);
    LOG_TMXINFO("tileId: ", frame.tiledId_);
    LOG_TMXINFO("duration: ", frame.duration_);
}

void TsxParser::ParseImageElement(tinyxml2::XMLElement* imageElement, Image& image)
{
    image.path_ = imageElement->Attribute("source");
    imageElement->QueryAttribute("width", &image.width_);
    imageElement->QueryAttribute("height", &image.height_);
    LOG_TMXINFO("source: ", image.path_);
    LOG_TMXINFO("width: ", image.width_, " height: ", image.height_);
}

}  // namespace Tile

}  // namespace FA
