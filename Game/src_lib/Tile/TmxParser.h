/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <utility>
#include <vector>

namespace tinyxml2 {

class XMLElement;

}  // namespace tinyxml2

namespace FA {

namespace Tile {

class TmxParser
{
public:
    struct Map
    {
        std::string renderOrder_{};
        int width_{};
        int height_{};
        int tileWidth_{};
        int tileHeight_{};
    };

    struct TileSet
    {
        int firstGid_{};
        std::string tsxSource_{};
    };

    struct Layer
    {
        int id_{};
        std::string name_{};
        int width_{};
        int height_{};
        std::vector<int> tileIds_{};
    };

    struct Object
    {
        using Property = std::pair<std::string, std::string>;

        int id_{};
        std::string type_{};
        int x_{};
        int y_{};
        std::vector<Property> properties_;
    };

    struct Group
    {
        int id_{};
        std::string name_{};
        std::vector<Object> objects_{};
    };

    Map map_;
    std::vector<TileSet> tileSets_;
    std::vector<Layer> layers_;
    std::vector<Group> objectGroups_;

public:
    TmxParser();
    ~TmxParser();
    bool Parse(const std::string& fileName);

private:
    void ParseMapElement(tinyxml2::XMLElement* mapElement);
    void ParseTileSetElement(tinyxml2::XMLElement* tileSetElement, TileSet& tileSet);
    void ParseLayerElement(tinyxml2::XMLElement* layerElement, Layer& layer);
    void ParseDataElement(tinyxml2::XMLElement* dataElement, std::vector<int>& ids);
    void ParseObjectGroupElement(tinyxml2::XMLElement* layerElement, Group& group);
    void ParseObjectElement(tinyxml2::XMLElement* objectElement, Object& object);
    void ParsePropertyElement(tinyxml2::XMLElement* objectElement, TmxParser::Object::Property& prop);
};

}  // namespace Tile

}  // namespace FA
