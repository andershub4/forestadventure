/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include "TileMapData.h"

namespace FA {

namespace Tile {

struct ParsedTmx;

class TileMapParser
{
public:
    TileMapParser();
    ~TileMapParser();

    TileMapData Run(const std::string& fileName);

private:
    TileMapData tileMapData_;

private:
    void ReadMapProperties(const ParsedTmx& parsedTmx);
    void ReadTileSets(const ParsedTmx& parsedTmx, const std::string& tmxDir);
    void ReadLayers(const ParsedTmx& parsedTmx);
    void ReadObjectGroups(const ParsedTmx& parsedTmx);
    std::string GetXmlBuffer(const std::string& fileName) const;
    std::vector<int> ParseData(const std::string& dataStr) const;
};

}  // namespace Tile

}  // namespace FA
