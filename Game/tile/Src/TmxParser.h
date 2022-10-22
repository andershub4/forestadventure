/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include "BasicParseHelper.h"
#include "BasicTmxParser.h"

#include "TmxLogging.h"

namespace FA {

namespace Tile {

template <class DocumentT, class ElementT, class ErrorT>
class TmxParser : public BasicTmxParser<DocumentT, ElementT, ErrorT>
{
public:
    TmxParser(std::shared_ptr<BasicParseHelper<ElementT, ErrorT>> helper)
        : helper_(helper)
    {}

    virtual ~TmxParser() = default;

    virtual bool Parse(DocumentT& xmlDocument, const std::string& xmlBuffer, ParsedTmx& parsedTmx) const override
    {
        xmlDocument.Parse(xmlBuffer.c_str());

        if (xmlDocument.Error()) {
            return false;
        }
        else {
            ElementT* map = xmlDocument.FirstChildElement("map");
            ParseMapElement(map, parsedTmx);
            return true;
        }
    }

private:
    std::shared_ptr<BasicParseHelper<ElementT, ErrorT>> helper_;

private:
    void ParseMapElement(ElementT* mapElement, ParsedTmx& parsedTmx) const
    {
        helper_->ParseMap(mapElement, parsedTmx.map_);
        LOG_TMXINFO("map: ", parsedTmx.map_);

        auto tileSetElement = mapElement->FirstChildElement("tileset");
        while (tileSetElement != nullptr) {
            ParsedTmxTileSet set;
            helper_->ParseTmxTileSet(tileSetElement, set);
            LOG_TMXINFO("set: ", set);
            parsedTmx.tileSets_.push_back(set);
            tileSetElement = tileSetElement->NextSiblingElement("tileset");
        }

        auto layerElement = mapElement->FirstChildElement("layer");
        while (layerElement != nullptr) {
            ParsedLayer layer;
            helper_->ParseLayer(layerElement, layer);
            LOG_TMXINFO("layer: ", layer);
            parsedTmx.layers_.push_back(layer);
            layerElement = layerElement->NextSiblingElement("layer");
        }

        auto objectGroupElement = mapElement->FirstChildElement("objectgroup");
        while (objectGroupElement != nullptr) {
            ParsedObjectGroup group;
            helper_->ParseObjectGroup(objectGroupElement, group);
            LOG_TMXINFO("group: ", group);
            parsedTmx.objectGroups_.push_back(group);
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
};

}  // namespace Tile

}  // namespace FA
