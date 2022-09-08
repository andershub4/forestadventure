/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace FA {

namespace Tile {

struct Image
{
    Image(const std::string& path, unsigned int nCols, unsigned int nRows)
        : path_(path)
        , nCols_(nCols)
        , nRows_(nRows)
    {}

    Image(const std::string& path)
        : path_(path)
        , nCols_(1)
        , nRows_(1)
    {}

    std::string path_;
    unsigned int nCols_{};
    unsigned int nRows_{};
};

bool operator==(const Image& lhs, const Image& rhs);
std::ostream& operator<<(std::ostream& os, const Image& p);

struct Frame
{
    std::string texturePath_;
    unsigned int column_{};
    unsigned int row_{};
    unsigned int width_{};
    unsigned int height_{};
};

bool operator==(const Frame& lhs, const Frame& rhs);
std::ostream& operator<<(std::ostream& os, const Frame& p);

struct FrameData
{
    Frame frame_{};
    std::vector<Frame> frames_;
};

bool operator==(const FrameData& lhs, const FrameData& rhs);
std::ostream& operator<<(std::ostream& os, const FrameData& p);

struct TileSetData
{
    std::vector<Image> images_;
    std::unordered_map<int, FrameData> lookupTable_;
};

bool operator==(const TileSetData& lhs, const TileSetData& rhs);
std::ostream& operator<<(std::ostream& os, const TileSetData& p);

struct TileMapData
{
    struct MapProperties
    {
        unsigned int width_{};
        unsigned int height_{};
        unsigned int tileWidth_{};
        unsigned int tileHeight_{};
    };

    struct Layer
    {
        std::string name_{};
        std::vector<int> tileIds_;
    };

    struct Object
    {
        std::string typeStr_{};
        int x_{};
        int y_{};
        std::unordered_map<std::string, std::string> properties_;
    };

    struct ObjectGroup
    {
        std::string name_{};
        std::vector<Object> objects_;
    };

    MapProperties mapProperties_;
    std::map<int, TileSetData, std::greater<int>> tileSets_;
    std::vector<Layer> layers_;
    std::vector<ObjectGroup> objectGroups_;
};

bool operator==(const TileMapData::MapProperties& lhs, const TileMapData::MapProperties& rhs);
std::ostream& operator<<(std::ostream& os, const TileMapData::MapProperties& p);

bool operator==(const TileMapData::Layer& lhs, const TileMapData::Layer& rhs);
std::ostream& operator<<(std::ostream& os, const TileMapData::Layer& p);

bool operator==(const TileMapData::Object& lhs, const TileMapData::Object& rhs);
std::ostream& operator<<(std::ostream& os, const TileMapData::Object& p);

bool operator==(const TileMapData::ObjectGroup& lhs, const TileMapData::ObjectGroup& rhs);
std::ostream& operator<<(std::ostream& os, const TileMapData::ObjectGroup& p);

bool operator==(const TileMapData& lhs, const TileMapData& rhs);
std::ostream& operator<<(std::ostream& os, const TileMapData& p);

}  // namespace Tile

}  // namespace FA
