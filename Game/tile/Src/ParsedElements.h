/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "Print.h"

namespace FA {

namespace Tile {

using FA::operator<<;

/* first = attribute name, second = XMLError */
template <class ErrorT>
using ParseResult = std::tuple<std::string, ErrorT>;

struct ParsedMap
{
    std::string renderOrder_{};
    unsigned int width_{};
    unsigned int height_{};
    unsigned int tileWidth_{};
    unsigned int tileHeight_{};
};

inline bool operator==(const ParsedMap& lhs, const ParsedMap& rhs)
{
    return std::tie(lhs.renderOrder_, lhs.width_, lhs.height_, lhs.tileWidth_, lhs.tileHeight_) ==
           std::tie(rhs.renderOrder_, rhs.width_, rhs.height_, rhs.tileWidth_, rhs.tileHeight_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedMap& p)
{
    os << "renderOrder: " << p.renderOrder_ << " width: " << p.width_ << " height: " << p.height_
       << " tileWidth: " << p.tileWidth_ << " tileHeight: " << p.tileHeight_;

    return os;
}

struct ParsedTmxTileSet
{
    int firstGid_{};
    std::string tsxSource_{};
};

inline bool operator==(const ParsedTmxTileSet& lhs, const ParsedTmxTileSet& rhs)
{
    return std::tie(lhs.firstGid_, lhs.tsxSource_) == std::tie(rhs.firstGid_, rhs.tsxSource_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedTmxTileSet& p)
{
    os << "firstGid: " << p.firstGid_ << " tsxSource: " << p.tsxSource_;

    return os;
}

struct ParsedLayer
{
    int id_{};
    std::string name_{};
    unsigned int width_{};
    unsigned int height_{};
    std::string data_{};
};

inline bool operator==(const ParsedLayer& lhs, const ParsedLayer& rhs)
{
    return std::tie(lhs.id_, lhs.name_, lhs.width_, lhs.height_, lhs.data_) ==
           std::tie(rhs.id_, rhs.name_, rhs.width_, rhs.height_, rhs.data_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedLayer& p)
{
    os << "id: " << p.id_ << " name: " << p.name_ << " width: " << p.width_ << " height: " << p.height_
       << " data: " << p.data_;

    return os;
}

struct ParsedObject
{
    using Property = std::pair<std::string, std::string>;

    int id_{};
    std::string type_{};
    int x_{};
    int y_{};
    std::vector<Property> properties_;
};

inline bool operator==(const ParsedObject& lhs, const ParsedObject& rhs)
{
    return std::tie(lhs.id_, lhs.type_, lhs.x_, lhs.y_, lhs.properties_) ==
           std::tie(rhs.id_, rhs.type_, rhs.x_, rhs.y_, rhs.properties_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedObject& p)
{
    os << "id: " << p.id_ << " type: " << p.type_ << " x: " << p.x_ << " y: " << p.y_
       << " properties: " << p.properties_;

    return os;
}

struct ParsedObjectGroup
{
    int id_{};
    std::string name_{};
    std::vector<ParsedObject> objects_{};
};

inline bool operator==(const ParsedObjectGroup& lhs, const ParsedObjectGroup& rhs)
{
    return std::tie(lhs.id_, lhs.name_, lhs.objects_) == std::tie(rhs.id_, rhs.name_, rhs.objects_);
}

inline std::ostream& operator<<(std::ostream& os, const ParsedObjectGroup& p)
{
    os << "id: " << p.id_ << " name: " << p.name_ << " objects: " << p.objects_;

    return os;
}

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
