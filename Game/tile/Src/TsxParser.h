/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "BasicTsxParser.h"

#include "TmxLogging.h"

namespace FA {

namespace Tile {

template <class ElementT, class ErrorT>
class BasicParseHelper;

template <class DocumentT, class ElementT, class ErrorT>
class TsxParser : public BasicTsxParser<DocumentT, ElementT, ErrorT>
{
public:
    TsxParser(DocumentT& xmlDocument, BasicParseHelper<ElementT, ErrorT>& helper)
        : xmlDocument_(xmlDocument)
        , helper_(helper)
    {}

    virtual ~TsxParser() = default;

    virtual bool Parse(const std::string& xmlBuffer, ParsedTsx& parsedTsx) const override
    {
        xmlDocument_.Parse(xmlBuffer.c_str());

        if (xmlDocument_.Error()) {
            return false;
        }
        else {
            ElementT* tileSetElement = xmlDocument_.FirstChildElement("tileset");
            ParseTileSetElement(tileSetElement, parsedTsx);
            return true;
        }
    }

private:
    BasicParseHelper<ElementT, ErrorT>& helper_;
    DocumentT& xmlDocument_;

private:
    void ParseTileSetElement(ElementT* tileSetElement, ParsedTsx& parsedTsx) const
    {
        helper_.ParseTileSet(tileSetElement, parsedTsx.tileSet_);
        LOG_TMXINFO("tileSet: ", parsedTsx.tileSet_);

        auto tileElement = tileSetElement->FirstChildElement("tile");
        while (tileElement != nullptr) {
            ParsedTile tile;
            helper_.ParseTile(tileElement, tile);
            LOG_TMXINFO("tile: ", tile);
            parsedTsx.tiles_.push_back(tile);
            tileElement = tileElement->NextSiblingElement("tile");
        }

        auto imageElement = tileSetElement->FirstChildElement("image");
        if (imageElement != nullptr) {
            helper_.ParseImage(imageElement, parsedTsx.image_);
            LOG_TMXINFO("image: ", parsedTsx.image_);
        }
    }
};

}  // namespace Tile

}  // namespace FA
