/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <ostream>
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

inline bool operator==(const Image& lhs, const Image& rhs)
{
    return lhs.path_ == rhs.path_ && lhs.nCols_ == rhs.nCols_ && lhs.nRows_ == rhs.nRows_;
}

inline std::ostream& operator<<(std::ostream& os, const Image& p)
{
    os << "path: " << p.path_ << " nCols: " << p.nCols_ << " nRows: " << p.nRows_;

    return os;
}

struct Frame
{
    std::string texturePath_;
    unsigned int u_{};
    unsigned int v_{};
    unsigned int width_{};
    unsigned int height_{};
};

inline bool operator==(const Frame& lhs, const Frame& rhs)
{
    return std::tie(lhs.texturePath_, lhs.u_, lhs.v_, lhs.width_, lhs.height_) ==
           std::tie(rhs.texturePath_, rhs.u_, rhs.v_, rhs.width_, rhs.height_);
}

inline std::ostream& operator<<(std::ostream& os, const Frame& p)
{
    os << "texturePath: " << p.texturePath_ << " u: " << p.u_ << " v: " << p.v_ << " width: " << p.width_
       << " height: " << p.height_;

    return os;
}

struct FrameData
{
    FrameData() = default;
    FrameData(const std::vector<Frame>& frames)
        : frames_(frames)
    {}
    bool IsAnimation() { return frames_.size() > 1; }
    Frame Front() { return frames_.front(); }
    std::vector<Frame> GetFrames() const { return frames_; }

private:
    std::vector<Frame> frames_;
};

inline bool operator==(const FrameData& lhs, const FrameData& rhs)
{
    return lhs.GetFrames() == rhs.GetFrames();
}

struct TileMapData
{
    struct MapProperties
    {
        unsigned int width_{};
        unsigned int height_{};
        unsigned int tileWidth_{};
        unsigned int tileHeight_{};
    };

    struct TileSet
    {
        std::vector<Image> images_;
        std::unordered_map<int, FrameData> frameDatas_;
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
    std::map<int, TileSet, std::greater<int>> tileSets_;
    std::vector<Layer> layers_;
    std::vector<ObjectGroup> objectGroups_;
};

}  // namespace Tile

}  // namespace FA
