/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "FrameData.h"

namespace FA {

class SheetManager;

namespace Tile {

class BasicTileSet;
class TileMapReader;
struct TileMapData;

class TileMap
{
public:
    struct TileData
    {
        unsigned int x_{};
        unsigned int y_{};
        unsigned int scale_{};
        FrameData frameData_{};
    };

    struct ObjectData
    {
        std::string typeStr_{};
        unsigned int x_{};
        unsigned int y_{};
        unsigned int scale_{};
        std::unordered_map<std::string, std::string> properties_;
    };

public:
    TileMap(SheetManager &sheetManager, unsigned int scale);
    ~TileMap();
    void Load(const std::string &fileName);
    void Setup();
    const std::vector<TileData> &GetLayer(const std::string &name) const;
    const std::vector<ObjectData> GetObjectGroup(const std::string &name) const;
    sf::Vector2u GetSize() const;

private:
    SheetManager &sheetManager_;
    std::unique_ptr<TileMapData> tileMapData_ = nullptr;
    ;
    std::unique_ptr<TileMapReader> tileMapReader_ = nullptr;
    std::map<std::string, std::vector<TileData>> layers_;
    std::map<int, std::unique_ptr<BasicTileSet>, std::greater<int>> tileSets_;
    std::map<std::string, std::vector<ObjectData>> objectGroups_;
    unsigned int scale_{};

private:
    void LoadTileSets();
    void SetupLayers();
    void SetupObjectGroups();
    FrameData GetFrameData(int id);
};

}  // namespace Tile

}  // namespace FA
