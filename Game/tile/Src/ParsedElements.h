/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "Print.h"

namespace FA {

namespace Tile {

struct ParsedTileSet
{
    std::string name_{};
    unsigned int tileWidth_{};
    unsigned int tileHeight_{};
    unsigned int tileCount_{};
    unsigned int columns_{};
};

inline bool operator==(const ParsedTileSet& lhs, const ParsedTileSet& rhs)
{
    return std::tie(lhs.name_, lhs.tileWidth_, lhs.tileHeight_, lhs.tileCount_, lhs.columns_) ==
           std::tie(rhs.name_, rhs.tileWidth_, rhs.tileHeight_, rhs.tileCount_, rhs.columns_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedTileSet& p)
{
    os << "name: " << p.name_ << " tileWidth: " << p.tileWidth_ << " tileHeight: " << p.tileHeight_
       << " tileCount: " << p.tileCount_ << " columns: " << p.columns_;

    return os;
}

struct ParsedImage
{
    std::string source_;
    unsigned int width_{};
    unsigned int height_{};
};

inline bool operator==(const ParsedImage& lhs, const ParsedImage& rhs)
{
    return std::tie(lhs.source_, lhs.width_, lhs.height_) == std::tie(rhs.source_, rhs.width_, rhs.height_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedImage& p)
{
    os << "source: " << p.source_ << " width: " << p.width_ << " height: " << p.height_;

    return os;
}

struct ParsedFrame
{
    unsigned int id_{};
    unsigned int duration_{};
};

inline bool operator==(const ParsedFrame& lhs, const ParsedFrame& rhs)
{
    return std::tie(lhs.id_, lhs.duration_) == std::tie(rhs.id_, rhs.duration_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedFrame& p)
{
    os << "id: " << p.id_ << " duration: " << p.duration_;

    return os;
}

struct ParsedAnimation
{
    std::vector<ParsedFrame> frames_;
};

inline bool operator==(const ParsedAnimation& lhs, const ParsedAnimation& rhs)
{
    return lhs.frames_ == rhs.frames_;
}

inline std::ostream& operator<<(std::ostream& os, const ParsedAnimation& p)
{
    os << "frames: " << p.frames_;

    return os;
}

struct ParsedTile
{
    unsigned int id_{};
    ParsedImage image_;
    ParsedAnimation animation_;
};

inline bool operator==(const ParsedTile& lhs, const ParsedTile& rhs)
{
    return std::tie(lhs.id_, lhs.image_, lhs.animation_) == std::tie(rhs.id_, rhs.image_, rhs.animation_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedTile& p)
{
    os << "id: " << p.id_ << " image: " << p.image_ << " animation: " << p.animation_;

    return os;
}

}  // namespace Tile

}  // namespace FA
