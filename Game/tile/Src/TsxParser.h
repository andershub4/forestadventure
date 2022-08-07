/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Tile.h"
#include "TmxLogging.h"

namespace FA {

namespace Tile {

template <class D, class E>
class TsxParser
{
public:
    struct TileSet
    {
        std::string name_{};
        int tileWidth_{};
        int tileHeight_{};
        int tileCount_{};
        int columns_{};
    };

public:
    bool Parse(const std::string& fileName, D* xmlDocument)
    {
        xmlDocument->LoadFile(fileName.c_str());

        if (xmlDocument->Error()) {
            return false;
        }
        else {
            E* tileSetElement = xmlDocument->FirstChildElement("tileset");
            ParseTileSetElement(tileSetElement);
            return true;
        }
    }

    TileSet tileSet_;
    Image image_;
    std::vector<Tile> tiles_;  // or unordered_map?

private:
    void ParseTileSetElement(E* tileSetElement)
    {
        tileSet_.name_ = tileSetElement->Attribute("name");
        tileSetElement->QueryAttribute("tilewidth", &tileSet_.tileWidth_);
        tileSetElement->QueryAttribute("tileheight", &tileSet_.tileHeight_);
        tileSetElement->QueryAttribute("tilecount", &tileSet_.tileCount_);
        tileSetElement->QueryAttribute("columns", &tileSet_.columns_);
        LOG_TMXINFO("name: ", tileSet_.name_);
        LOG_TMXINFO("tileWidth: ", tileSet_.tileWidth_, " tileHeight: ", tileSet_.tileHeight_);
        LOG_TMXINFO("tileCount: ", tileSet_.tileCount_, " columns: ", tileSet_.columns_);

        E* tileElement = tileSetElement->FirstChildElement("tile");
        if (tileElement) {  // Collection of images
            while (tileElement != nullptr) {
                Tile tile;
                ParseTileElement(tileElement, tile);
                tiles_.push_back(tile);
                tileElement = tileElement->NextSiblingElement("tile");
            }
        }
        else {  // Based on grid image
            E* imageElement = tileSetElement->FirstChildElement("image");
            ParseImageElement(imageElement, image_);
        }
    }

    void ParseTileElement(E* tileElement, Tile& tile)
    {
        tileElement->QueryAttribute("id", &tile.id_);
        E* imageElement = tileElement->FirstChildElement("image");
        ParseImageElement(imageElement, tile.image_);
        E* animationElement = tileElement->FirstChildElement("animation");

        if (animationElement) {
            E* frameElement = animationElement->FirstChildElement("frame");

            while (frameElement != nullptr) {
                ParsedFrame frame;
                ParseFrameElement(frameElement, frame);
                tile.frames_.push_back(frame);
                frameElement = frameElement->NextSiblingElement("frame");
            }
        }
    }

    void ParseFrameElement(E* frameElement, ParsedFrame& frame)
    {
        frameElement->QueryAttribute("tileid", &frame.tiledId_);
        frameElement->QueryAttribute("duration", &frame.duration_);
        LOG_TMXINFO("tileId: ", frame.tiledId_);
        LOG_TMXINFO("duration: ", frame.duration_);
    }

    void ParseImageElement(E* imageElement, Image& image)
    {
        image.path_ = imageElement->Attribute("source");
        imageElement->QueryAttribute("width", &image.width_);
        imageElement->QueryAttribute("height", &image.height_);
        LOG_TMXINFO("source: ", image.path_);
        LOG_TMXINFO("width: ", image.width_, " height: ", image.height_);
    }
};

}  // namespace Tile

}  // namespace FA
