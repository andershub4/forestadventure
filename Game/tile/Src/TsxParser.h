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
    std::vector<ParsedTile> tiles_;
    BasicParseHelper<ElementT, Error>& helper_;

private:
    void ParseTileSetElement(ElementT* tileSetElement)
    {
        helper_.ParseTileSet(tileSetElement, tileSet_);
        LOG_TMXINFO("tileSet: ", tileSet_);

        auto tileElement = tileSetElement->FirstChildElement("tile");
        while (tileElement != nullptr) {
            ParsedTile tile;
            helper_.ParseTile(tileElement, tile);
            LOG_TMXINFO("tile: ", tile);
            tiles_.push_back(tile);
            tileElement = tileElement->NextSiblingElement("tile");
        }

        auto imageElement = tileSetElement->FirstChildElement("image");
        if (imageElement != nullptr) {
            helper_.ParseImage(imageElement, image_);
            LOG_TMXINFO("image: ", image_);
        }
    }
};

}  // namespace Tile

}  // namespace FA
