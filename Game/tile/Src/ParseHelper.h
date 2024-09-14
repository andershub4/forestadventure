/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "ParseHelperIf.h"

namespace FA {

namespace Tile {

template <class ElementT, class ErrorT>
class ParseHelper : public ParseHelperIf<ElementT, ErrorT>
{
public:
    virtual ~ParseHelper() = default;

    virtual std::vector<ParseResult<ErrorT>> ParseMap(ElementT* element, ParsedMap& map) const override
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "renderorder", map.renderOrder_)},
                                                 {ParseElement(element, "width", map.width_)},
                                                 {ParseElement(element, "height", map.height_)},
                                                 {ParseElement(element, "tilewidth", map.tileWidth_)},
                                                 {ParseElement(element, "tileheight", map.tileHeight_)}};

        return results;
    }

    virtual std::vector<ParseResult<ErrorT>> ParseTmxTileSet(ElementT* element,
                                                             ParsedTmxTileSet& tileSet) const override
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "firstgid", tileSet.firstGid_)},
                                                 {ParseElement(element, "source", tileSet.tsxSource_)}};

        return results;
    }

    virtual std::vector<ParseResult<ErrorT>> ParseLayer(ElementT* element, ParsedLayer& layer) const override
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "id", layer.id_)},
                                                 {ParseElement(element, "name", layer.name_)},
                                                 {ParseElement(element, "width", layer.width_)},
                                                 {ParseElement(element, "height", layer.height_)}};
        auto dataElement = element->FirstChildElement("data");
        if (dataElement) {
            layer.data_ = dataElement->GetText();
        }

        return results;
    }

    virtual std::vector<ParseResult<ErrorT>> ParseObjectGroup(ElementT* element,
                                                              ParsedObjectGroup& group) const override
    {
        std::vector<ParseResult<ErrorT>> results{ParseElement(element, "id", group.id_),
                                                 ParseElement(element, "name", group.name_)};
        auto r1 = ParseObjects(element, group.objects_);
        results.insert(results.end(), r1.begin(), r1.end());

        return results;
    }

    virtual std::vector<ParseResult<ErrorT>> ParseTileSet(ElementT* element, ParsedTileSet& tileSet) const override
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "name", tileSet.name_)},
                                                 {ParseElement(element, "tilewidth", tileSet.tileWidth_)},
                                                 {ParseElement(element, "tileheight", tileSet.tileHeight_)},
                                                 {ParseElement(element, "tilecount", tileSet.tileCount_)},
                                                 {ParseElement(element, "columns", tileSet.columns_)}};

        return results;
    }

    virtual std::vector<ParseResult<ErrorT>> ParseImage(ElementT* element, ParsedImage& image) const override
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "source", image.source_)},
                                                 {ParseElement(element, "width", image.width_)},
                                                 {ParseElement(element, "height", image.height_)}};

        return results;
    }

    virtual std::vector<ParseResult<ErrorT>> ParseTile(ElementT* element, ParsedTile& tile) const override
    {
        std::vector<ParseResult<ErrorT>> results;
        auto r1 = ParseElement(element, "id", tile.id_);
        results.push_back(r1);
        auto imageElement = element->FirstChildElement("image");
        auto r2 = ParseImage(imageElement, tile.image_);
        results.insert(results.end(), r2.begin(), r2.end());
        auto animationElement = element->FirstChildElement("animation");
        auto r3 = ParseAnimation(animationElement, tile.animation_);
        results.insert(results.end(), r3.begin(), r3.end());

        return results;
    }

private:
    template <class ValueT>
    auto ParseElement(ElementT* element, const std::string& attrName, ValueT& attrValue) const
    {
        auto r = element->QueryAttribute(attrName.c_str(), &attrValue);
        return std::make_tuple(attrName, r);
    }

    template <class ValueT>
    auto ParseOptionalElement(ElementT* element, const std::string& attrName, ValueT& attrValue) const
    {
        element->QueryAttribute(attrName.c_str(), &attrValue);
        return std::make_tuple(attrName, ErrorT::XML_SUCCESS);
    }

    template <>
    auto ParseElement(ElementT* element, const std::string& attrName, std::string& attrValue) const
    {
        const char* charPtr = nullptr;
        auto r = element->QueryStringAttribute(attrName.c_str(), &charPtr);
        if (charPtr) attrValue = charPtr;
        return std::make_tuple(attrName, r);
    }

    std::vector<ParseResult<ErrorT>> ParseProperty(ElementT* element, ParsedObject::Property& property) const
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "name", property.first)},
                                                 {ParseElement(element, "value", property.second)}};

        return results;
    }

    std::vector<ParseResult<ErrorT>> ParseProperties(ElementT* parentElement,
                                                     std::vector<ParsedObject::Property>& properties) const
    {
        std::vector<ParseResult<ErrorT>> results;
        auto propertiesElement = parentElement->FirstChildElement("properties");

        if (propertiesElement) {
            auto element = propertiesElement->FirstChildElement("property");
            while (element != nullptr) {
                ParsedObject::Property property;
                auto r = ParseProperty(element, property);
                properties.push_back(property);
                results.insert(results.end(), r.begin(), r.end());
                element = element->NextSiblingElement("property");
            }
        }

        return results;
    }

    std::vector<ParseResult<ErrorT>> ParseObject(ElementT* element, ParsedObject& object) const
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "id", object.id_)},
                                                 {ParseElement(element, "type", object.type_)},
                                                 {ParseElement(element, "x", object.x_)},
                                                 {ParseElement(element, "y", object.y_)},
                                                 {ParseOptionalElement(element, "width", object.width_)},
                                                 {ParseOptionalElement(element, "height", object.height_)}};

        auto r1 = ParseProperties(element, object.properties_);
        results.insert(results.end(), r1.begin(), r1.end());

        return results;
    }

    std::vector<ParseResult<ErrorT>> ParseObjects(ElementT* parentElement, std::vector<ParsedObject>& objects) const
    {
        std::vector<ParseResult<ErrorT>> results;
        auto element = parentElement->FirstChildElement("object");

        while (element != nullptr) {
            ParsedObject object;
            auto r = ParseObject(element, object);
            objects.push_back(object);
            results.insert(results.end(), r.begin(), r.end());
            element = element->NextSiblingElement("object");
        }

        return results;
    }

    std::vector<ParseResult<ErrorT>> ParseFrame(ElementT* element, ParsedFrame& frame) const
    {
        std::vector<ParseResult<ErrorT>> results{{ParseElement(element, "tileid", frame.id_)},
                                                 {ParseElement(element, "duration", frame.duration_)}};

        return results;
    }

    std::vector<ParseResult<ErrorT>> ParseFrames(ElementT* parentElement, std::vector<ParsedFrame>& frames) const
    {
        std::vector<ParseResult<ErrorT>> results;
        auto element = parentElement->FirstChildElement("frame");

        while (element != nullptr) {
            ParsedFrame frame;
            auto r = ParseFrame(element, frame);
            frames.push_back(frame);
            results.insert(results.end(), r.begin(), r.end());
            element = element->NextSiblingElement("frame");
        }

        return results;
    }

    std::vector<ParseResult<ErrorT>> ParseAnimation(ElementT* element, ParsedAnimation& animation) const
    {
        if (element != nullptr) {
            return ParseFrames(element, animation.frames_);
        }

        return {};
    }
};

}  // namespace Tile

}  // namespace FA
