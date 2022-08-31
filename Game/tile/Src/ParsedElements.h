/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>
#include <string>
#include <vector>

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
    return lhs.name_ == rhs.name_ && lhs.tileWidth_ == rhs.tileWidth_ && lhs.tileHeight_ == rhs.tileHeight_ &&
           lhs.tileCount_ == rhs.tileCount_ && lhs.columns_ == rhs.columns_;
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
    return lhs.source_ == rhs.source_ && lhs.width_ == rhs.width_ && lhs.height_ == rhs.height_;
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
    return lhs.id_ == rhs.id_ && lhs.duration_ == rhs.duration_;
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
    os << "frames: { ";
    for (const auto& frame : p.frames_) {
        os << frame << " ";
    }
    os << "}";

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
    return lhs.id_ == rhs.id_ && lhs.image_ == rhs.image_ && lhs.animation_ == rhs.animation_;
}

inline std::ostream& operator<<(std::ostream& os, const ParsedTile& p)
{
    os << "id: " << p.id_ << " image: " << p.image_ << " animation: " << p.animation_;

    return os;
}

}  // namespace Tile

}  // namespace FA
