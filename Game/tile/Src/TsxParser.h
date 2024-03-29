/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ParseHelperIf.h"
#include "TsxParserIf.h"

#include "TmxLogging.h"

namespace FA {

namespace Tile {

template <class DocumentT, class ElementT, class ErrorT>
class TsxParser : public TsxParserIf<DocumentT, ElementT, ErrorT>
{
public:
    TsxParser(std::shared_ptr<ParseHelperIf<ElementT, ErrorT>> helper)
        : helper_(helper)
    {}

    virtual bool Parse(DocumentT& xmlDocument, const std::string& xmlBuffer, ParsedTsx& parsedTsx) const override
    {
        xmlDocument.Parse(xmlBuffer.c_str());

        if (xmlDocument.Error()) {
            LOG_TMXERROR("tinyxml2 error: %s", xmlDocument.ErrorName());
            return false;
        }
        else {
            ElementT* tileSetElement = xmlDocument.FirstChildElement("tileset");
            if (tileSetElement != nullptr) {
                ParseTileSetElement(tileSetElement, parsedTsx);
                return true;
            }
            LOG_TMXERROR("Error while parsing: tileset element does not exist");
            return false;
        }
    }

private:
    std::shared_ptr<ParseHelperIf<ElementT, ErrorT>> helper_;

private:
    void ParseTileSetElement(ElementT* tileSetElement, ParsedTsx& parsedTsx) const
    {
        helper_->ParseTileSet(tileSetElement, parsedTsx.tileSet_);
        LOG_TMXDEBUG("%s", DUMP(parsedTsx.tileSet_));

        auto tileElement = tileSetElement->FirstChildElement("tile");
        while (tileElement != nullptr) {
            ParsedTile tile;
            helper_->ParseTile(tileElement, tile);
            LOG_TMXDEBUG("%s", DUMP(tile));
            parsedTsx.tiles_.push_back(tile);
            tileElement = tileElement->NextSiblingElement("tile");
        }

        auto imageElement = tileSetElement->FirstChildElement("image");
        if (imageElement != nullptr) {
            helper_->ParseImage(imageElement, parsedTsx.image_);
            LOG_TMXDEBUG("%s", DUMP(parsedTsx.image_));
        }
    }
};

}  // namespace Tile

}  // namespace FA
