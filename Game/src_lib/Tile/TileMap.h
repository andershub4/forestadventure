/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "FrameData.h"
#include "Fwd/SfmlFwd.h"
#include "TileMapData.h"

namespace FA {

class SheetManager;

namespace Tile {

class BasicTileSet;
class TileMapReader;

class TileMap
{
public:
    struct TileData
    {
        sf::Vector2u position_{};
        unsigned int scale_{};
        FrameData frameData_{};
    };

    struct ObjectData
    {
        std::string typeStr_{};
        sf::Vector2u position_{};
        unsigned int scale_{};
        std::string faceDirStr_{};
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
    TileMapData tileMapData_;
    std::unique_ptr<TileMapReader> tileMapReader_ = nullptr;
    std::map<std::string, std::vector<TileData>> layers_;
    std::map<int, std::unique_ptr<BasicTileSet>, std::greater<int>> tileSets_;
    std::map<std::string, std::vector<ObjectData>> objectGroups_;
    unsigned int scale_{};

private:
    void LoadTileSets();
    void SetupLayers();
    void SetupObjectGroups();
    std::unique_ptr<BasicTileSet> CreateTileSet(const TileMapData::TileSet &tileSet) const;
    FrameData GetFrameData(int id);
};

}  // namespace Tile

}  // namespace FA
