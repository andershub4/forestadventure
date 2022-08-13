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
#include "ParsedTileSetData.h"

namespace FA {

namespace Tile {

template <class ElementT, class ErrorT>
class ParseHelper : BasicParseHelper<ElementT, ErrorT>
{
public:
    virtual bool ParseTileSet(ElementT* element, TileSetData& data) const override
    {
        const char* name = nullptr;
        auto r0 = element->QueryStringAttribute("name", &name);
        if (name) data.name_ = name;
        auto r1 = element->QueryAttribute("tilewidth", &data.tileWidth_);
        auto r2 = element->QueryAttribute("tileheight", &data.tileHeight_);
        auto r3 = element->QueryAttribute("tilecount", &data.tileCount_);
        auto r4 = element->QueryAttribute("columns", &data.columns_);

        std::vector<ErrorT> results{r0, r1, r2, r3, r4};
        bool result =
            std::all_of(results.begin(), results.end(), [](const ErrorT& e) { return e == ErrorT::XML_SUCCESS; });

        return result;
    }
};

}  // namespace Tile

}  // namespace FA
