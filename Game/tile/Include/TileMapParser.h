/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>

namespace tinyxml2 {

class XMLElement;
class XMLDocument;
enum XMLError;

}  // namespace tinyxml2

namespace FA {

namespace Tile {

struct TileMapData;

template <class ElementT, class ErrorT>
class ParseHelper;

template <class DocumentT, class ElementT, class ErrorT>
class TmxParser;

template <class DocumentT, class ElementT, class ErrorT>
class TsxParser;

template <class DocumentT, class ElementT, class ErrorT>
class TileService;

class TileMapParser
{
public:
    TileMapParser();
    ~TileMapParser();

    TileMapData Run(const std::string& fileName);

private:
    using ParseHelperImpl = ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>;
    using TileServiceImpl = TileService<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>;
    using TmxParserImpl = TmxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>;
    using TsxParserImpl = TsxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>;

    std::shared_ptr<ParseHelperImpl> helper_;
    std::unique_ptr<TileServiceImpl> tileService_;
};

}  // namespace Tile

}  // namespace FA
