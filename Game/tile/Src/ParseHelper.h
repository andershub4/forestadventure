/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "BasicParseHelper.h"

namespace FA {

namespace Tile {

template <class DocumentT, class ElementT, class ErrorT>
class ParseHelper : BasicParseHelper<DocumentT, ElementT, ErrorT>
{
public:
    virtual ~ParseHelper() = default;

    virtual bool ParseTileSet(DocumentT* document, ParsedTileSetData& data) const override
    {
        auto element = document->FirstChildElement("tileset");
        const char* name = nullptr;
        auto r0 = element->QueryStringAttribute("name", &name);
        if (name) data.name_ = name;
        auto r1 = element->QueryAttribute("tilewidth", &data.tileWidth_);
        auto r2 = element->QueryAttribute("tileheight", &data.tileHeight_);
        auto r3 = element->QueryAttribute("tilecount", &data.tileCount_);
        auto r4 = element->QueryAttribute("columns", &data.columns_);

        std::vector<ErrorT> results{r0, r1, r2, r3, r4};
        return Result(results);
    }

    virtual bool ParseImage(ElementT* parentElement, ParsedImage& image) const override
    {
        auto element = parentElement->FirstChildElement("image");
        const char* source = nullptr;
        auto r0 = element->QueryStringAttribute("source", &source);
        if (source) image.source_ = source;
        auto r1 = element->QueryAttribute("width", &image.width_);
        auto r2 = element->QueryAttribute("height", &image.height_);

        std::vector<ErrorT> results{r0, r1, r2};
        return Result(results);
    }

    virtual bool ParseTiles(ElementT* parentElement, std::vector<ParsedTile>& tiles) const override
    {
        auto element = parentElement->FirstChildElement("tile");
        bool result = true;

        while (element != nullptr) {
            ParsedTile tile;
            auto r = ParseTile(element, tile);
            result &= r;
            tiles.push_back(tile);
            element = element->NextSiblingElement("tile");
        }

        return result;
    }

private:
    bool ParseTile(ElementT* element, ParsedTile& tile) const
    {
        auto r0 = element->QueryAttribute("id", &tile.id_);
        auto i = ParseImage(element, tile.image_);

        return ((r0 == ErrorT::XML_SUCCESS) && i);
    }

    bool Result(const std::vector<ErrorT>& results) const
    {
        return std::all_of(results.begin(), results.end(), [](const ErrorT& e) { return e == ErrorT::XML_SUCCESS; });
    }
};

}  // namespace Tile

}  // namespace FA
