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

template <class ElementT, class ErrorT>
class ParseHelper : public BasicParseHelper<ElementT, ErrorT>
{
public:
    virtual ~ParseHelper() = default;

    virtual bool ParseTileSet(ElementT* element, ParsedTileSetData& data) const override
    {
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

    virtual bool ParseImage(ElementT* element, ParsedImage& image) const override
    {
        const char* source = nullptr;
        auto r0 = element->QueryStringAttribute("source", &source);
        if (source) image.source_ = source;
        auto r1 = element->QueryAttribute("width", &image.width_);
        auto r2 = element->QueryAttribute("height", &image.height_);

        std::vector<ErrorT> results{r0, r1, r2};
        return Result(results);
    }

    bool ParseTile(ElementT* element, ParsedTile& tile) const override
    {
        auto r0 = element->QueryAttribute("id", &tile.id_);
        auto imageElement = element->FirstChildElement("image");
        auto i = ParseImage(imageElement, tile.image_);
        auto animationElement = element->FirstChildElement("animation");
        auto a = ParseAnimation(animationElement, tile.animation_);

        return ((r0 == ErrorT::XML_SUCCESS) && i && a);
    }

private:
    bool ParseFrame(ElementT* element, ParsedFrame& frame) const
    {
        auto r1 = element->QueryAttribute("tileid", &frame.id_);
        auto r2 = element->QueryAttribute("duration", &frame.duration_);

        std::vector<ErrorT> results{r1, r2};
        return Result(results);
    }

    bool ParseFrames(ElementT* parentElement, std::vector<ParsedFrame>& frames) const
    {
        auto element = parentElement->FirstChildElement("frame");
        bool result = true;

        while (element != nullptr) {
            ParsedFrame frame;
            auto r = ParseFrame(element, frame);
            result &= r;
            frames.push_back(frame);
            element = element->NextSiblingElement("frame");
        }

        return result;
    }

    bool ParseAnimation(ElementT* element, ParsedAnimation& animation) const
    {
        if (element != nullptr) {
            return ParseFrames(element, animation.frames_);
        }

        return true;
    }

    bool Result(const std::vector<ErrorT>& results) const
    {
        return std::all_of(results.begin(), results.end(), [](const ErrorT& e) { return e == ErrorT::XML_SUCCESS; });
    }
};

}  // namespace Tile

}  // namespace FA
