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

struct ParsedTsx
{
    ParsedTileSetData tileSet_;
    ParsedImage image_;
    std::vector<ParsedTile> tiles_;
};

inline bool operator==(const ParsedTsx& lhs, const ParsedTsx& rhs)
{
    return lhs.image_ == rhs.image_ && lhs.tileSet_ == rhs.tileSet_ && lhs.tiles_ == rhs.tiles_;
}

inline std::ostream& operator<<(std::ostream& os, const ParsedTsx& p)
{
    os << "tileSet: " << p.tileSet_ << " image: " << p.image_;

    os << " tiles: { ";
    for (const auto& tile : p.tiles_) {
        os << tile << " ";
    }
    os << "}";

    return os;
}

template <class DocumentT, class ElementT, class Error>
class TsxParser
{
public:
    TsxParser(BasicParseHelper<ElementT, Error>& helper)
        : helper_(helper)
    {}

public:
    bool Parse(const std::string& fileName, DocumentT* xmlDocument, ParsedTsx& parsedTsx)
    {
        xmlDocument->LoadFile(fileName.c_str());

        if (xmlDocument->Error()) {
            return false;
        }
        else {
            ElementT* tileSetElement = xmlDocument->FirstChildElement("tileset");
            ParseTileSetElement(tileSetElement, parsedTsx);
            return true;
        }
    }

    BasicParseHelper<ElementT, Error>& helper_;

private:
    void ParseTileSetElement(ElementT* tileSetElement, ParsedTsx& parsedTsx)
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
