/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ParsedElements.h"
#include "TmxLogging.h"

namespace FA {

namespace Tile {

template <class ElementT, class Error>
class BasicParseHelper;

template <class DocumentT, class ElementT, class Error>
class TsxParser
{
public:
    TsxParser(BasicParseHelper<ElementT, Error>& helper)
        : helper_(helper)
    {}

public:
    bool Parse(const std::string& fileName, DocumentT* xmlDocument)
    {
        xmlDocument->LoadFile(fileName.c_str());

        if (xmlDocument->Error()) {
            return false;
        }
        else {
            ElementT* tileSetElement = xmlDocument->FirstChildElement("tileset");
            ParseTileSetElement(tileSetElement);
            return true;
        }
    }

    ParsedTileSetData tileSet_;
    ParsedImage image_;
    std::vector<ParsedTile> tiles_;  // or unordered_map?
    BasicParseHelper<ElementT, Error>& helper_;

private:
    void ParseTileSetElement(ElementT* tileSetElement)
    {
        helper_.ParseTileSet(tileSetElement, tileSet_);
        LOG_TMXINFO("name: ", tileSet_.name_);
        LOG_TMXINFO("tileWidth: ", tileSet_.tileWidth_, " tileHeight: ", tileSet_.tileHeight_);
        LOG_TMXINFO("tileCount: ", tileSet_.tileCount_, " columns: ", tileSet_.columns_);

        auto tileElement = tileSetElement->FirstChildElement("tile");
        while (tileElement != nullptr) {
            ParsedTile tile;
            helper_.ParseTile(tileElement, tile);
            LOG_TMXINFO("source: ", tile.image_.source_);
            LOG_TMXINFO("width: ", tile.image_.width_, " height: ", tile.image_.height_);
            for (const auto& frame : tile.animation_.frames_) {
                LOG_TMXINFO("tileId: ", frame.id_);
                LOG_TMXINFO("duration: ", frame.duration_);
            }
            tiles_.push_back(tile);
            tileElement = tileElement->NextSiblingElement("tile");
        }

        auto imageElement = tileSetElement->FirstChildElement("image");
        if (imageElement != nullptr) {
            helper_.ParseImage(imageElement, image_);
            LOG_TMXINFO("source: ", image_.source_);
            LOG_TMXINFO("width: ", image_.width_, " height: ", image_.height_);
        }
    }
};

}  // namespace Tile

}  // namespace FA
