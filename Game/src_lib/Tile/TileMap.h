/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <string>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>

#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"
#include "Fwd/SfmlFwd.h"
#include "TileMapData.h"

namespace FA {

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
    TileMap(const TileMapData &tileMapData);
    ~TileMap();
    void Create();
    const std::vector<sf::Sprite> &GetLayer(const std::string &name);
    const std::vector<ObjectData> GetObjectGroup(const std::string &name);
    sf::Vector2u GetSize() const;

private:
    struct TileInfo
    {
        const sf::Texture *texture_ = nullptr;
        sf::IntRect uvRect_;
    };

    static const unsigned int scale{2};

    TileMapData tileMapData_;
    std::map<std::string, std::vector<sf::Sprite>> layers_;
    std::map<std::string, std::vector<ObjectData>> objectGroups_;

private:
    TileInfo GetTileInfo(int id);
    EntityType ObjTypeStrToEnum(const std::string &typeStr) const;
    FaceDirection FaceDirStrToEnum(const std::string &faceDirStr) const;
};

}  // namespace Tile

}  // namespace FA
