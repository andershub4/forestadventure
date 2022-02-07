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

#include <SFML/Graphics/Sprite.hpp>

#include "BasicTileSet.h"
#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"
#include "Fwd/SfmlFwd.h"
#include "TileMapData.h"

namespace FA {

class SheetManager;

namespace Tile {

class TileMap
{
public:
    struct ObjectData
    {
        EntityType type_{};
        sf::Vector2u position_{};
        FaceDirection faceDir_{};
    };

public:
    TileMap(SheetManager &sheetManager, unsigned int scale);
    ~TileMap();
    void Create(const TileMapData &tileMapData);
    const std::vector<sf::Sprite> &GetLayer(const std::string &name);
    const std::vector<ObjectData> GetObjectGroup(const std::string &name);
    sf::Vector2u GetSize() const;
    unsigned int GetScale() const { return scale_; }

private:
    SheetManager &sheetManager_;
    TileMapData tileMapData_;
    std::map<std::string, std::vector<sf::Sprite>> layers_;
    std::map<int, std::unique_ptr<BasicTileSet>, std::greater<int>> tileSets_;
    std::map<std::string, std::vector<ObjectData>> objectGroups_;
    unsigned int scale_{};

private:
    void CreateTileSets();
    void CreateLayers();
    void CreateObjectGroups();
    std::unique_ptr<BasicTileSet> CreateTileSet(const TileMapData::TileSet &tileSet) const;
    Tile GetTileInfo(int id);
    EntityType ObjTypeStrToEnum(const std::string &typeStr) const;
    FaceDirection FaceDirStrToEnum(const std::string &faceDirStr) const;
};

}  // namespace Tile

}  // namespace FA
