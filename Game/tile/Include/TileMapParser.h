/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "TileMapData.h"

namespace tinyxml2 {

class XMLElement;
class XMLDocument;
enum XMLError;

}  // namespace tinyxml2

namespace FA {

namespace Tile {

struct ParsedTmx;
class TileSetFactory;

template <class ElementT, class ErrorT>
class ParseHelper;

template <class DocumentT, class ElementT, class ErrorT>
class TmxParser;

template <class DocumentT, class ElementT, class ErrorT>
class TsxParser;

class TileMapParser
{
public:
    TileMapParser();
    ~TileMapParser();

    TileMapData Run(const std::string& fileName);

private:
    TileMapData tileMapData_;
    std::unique_ptr<TileSetFactory> tileSetFactory_{};
    std::unique_ptr<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>> helper_{};
    std::unique_ptr<TmxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>> tmxParser_{};
    std::unique_ptr<TsxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>> tsxParser_{};

private:
    void ReadMapProperties(const ParsedTmx& parsedTmx);
    void ReadTileSets(const ParsedTmx& parsedTmx, const std::string& tmxDir);
    void ReadLayers(const ParsedTmx& parsedTmx);
    void ReadObjectGroups(const ParsedTmx& parsedTmx);
    std::vector<int> ParseData(const std::string& dataStr) const;
};

}  // namespace Tile

}  // namespace FA
