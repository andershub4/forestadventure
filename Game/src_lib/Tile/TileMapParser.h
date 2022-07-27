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
class TsxParser;

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
    TileMapData::Image GetImage(const std::string& tsxDir, const TsxParser& tsxParser) const;
    std::vector<TileMapData::Tile> GetTiles(const std::string& tsxDir, const TsxParser& tsxParser) const;

    std::string GetFilePath(const std::string& baseDir, const std::string& source) const;
};

}  // namespace Tile

}  // namespace FA
