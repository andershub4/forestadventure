/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "TileMapData.h"

namespace FA {

namespace Tile {

class TmxParser;

class TileMapParser
{
public:
    TileMapParser();
    ~TileMapParser();

    TileMapData Run(const std::string& fileName);

private:
    TileMapData tileMapData_;

private:
    void ReadMapProperties(const TmxParser& tmxParser);
    void ReadTileSets(const TmxParser& tmxParser, const std::string& tmxDir);
    void ReadLayers(const TmxParser& tmxParser);
    void ReadObjectGroups(const TmxParser& tmxParser);
};

}  // namespace Tile

}  // namespace FA
