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

#include "Resource/Frame.h"

namespace FA {

namespace Shared {

class SheetManager;

}  // namespace Shared

namespace Tile {

class TileMapParser;
struct TileMapData;
struct FrameData;

class TileMap
{
public:
    struct TileData
    {
        unsigned int x_{};
        unsigned int y_{};
        Shared::Frame frame_;
        std::vector<Shared::Frame> frames_;
    };

    struct ObjectData
    {
        std::string typeStr_{};
        unsigned int x_{};
        unsigned int y_{};
        std::unordered_map<std::string, std::string> properties_;
    };

public:
    TileMap(Shared::SheetManager &sheetManager);
    ~TileMap();
    void Load(const std::string &fileName);
    void Setup();
    const std::vector<TileData> &GetLayer(const std::string &name) const;
    const std::vector<ObjectData> GetObjectGroup(const std::string &name) const;
    sf::Vector2u GetSize() const;

private:
    Shared::SheetManager &sheetManager_;
    std::unique_ptr<TileMapData> tileMapData_ = nullptr;
    std::unique_ptr<TileMapParser> tileMapParser_ = nullptr;
    std::map<std::string, std::vector<TileData>> layers_;
    std::map<std::string, std::vector<ObjectData>> objectGroups_;

private:
    void LoadTileSets();
    void SetupLayers();
    void SetupObjectGroups();
    FrameData GetFrameData(int id);
};

}  // namespace Tile

}  // namespace FA
