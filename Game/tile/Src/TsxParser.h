/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Tile.h"

namespace tinyxml2 {

class XMLElement;
class XMLDocument;

}  // namespace tinyxml2

namespace FA {

namespace Tile {

class TsxParser
{
public:
    struct TileSet
    {
        std::string name_{};
        int tileWidth_{};
        int tileHeight_{};
        int tileCount_{};
        int columns_{};
    };

public:
    TsxParser(std::unique_ptr<tinyxml2::XMLDocument> xmlDocument);
    ~TsxParser();
    bool Parse(const std::string& fileName);

    TileSet tileSet_;
    Image image_;
    std::vector<Tile> tiles_;  // or unordered_map?
    std::unique_ptr<tinyxml2::XMLDocument> xmlDocument_ = nullptr;

private:
    void ParseTileSetElement(tinyxml2::XMLElement* tileSetElement);
    void ParseImageElement(tinyxml2::XMLElement* imageElement, Image& image);
    void ParseTileElement(tinyxml2::XMLElement* tileElement, Tile& tile);
    void ParseFrameElement(tinyxml2::XMLElement* frameElement, ParsedFrame& frame);
};

}  // namespace Tile

}  // namespace FA
