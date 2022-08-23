/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Tile {

struct ParsedTileSetData
{
    std::string name_{};
    unsigned int tileWidth_{};
    unsigned int tileHeight_{};
    unsigned int tileCount_{};
    unsigned int columns_{};
};

inline bool operator==(const ParsedTileSetData& lhs, const ParsedTileSetData& rhs)
{
    return lhs.name_ == rhs.name_ && lhs.tileWidth_ == rhs.tileWidth_ && lhs.tileHeight_ == rhs.tileHeight_ &&
           lhs.tileCount_ == rhs.tileCount_ && lhs.columns_ == rhs.columns_;
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

struct ParsedFrame
{
    unsigned int id_{};
    unsigned int duration_{};
};

inline bool operator==(const ParsedFrame& lhs, const ParsedFrame& rhs)
{
    return lhs.id_ == rhs.id_ && lhs.duration_ == rhs.duration_;
}

struct ParsedAnimation
{
    std::vector<ParsedFrame> frames_;
};

inline bool operator==(const ParsedAnimation& lhs, const ParsedAnimation& rhs)
{
    return lhs.frames_ == rhs.frames_;
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

template <class ElementT, class ErrorT>
class BasicParseHelper
{
public:
    virtual ~BasicParseHelper() = default;

    virtual bool ParseTileSet(ElementT* element, ParsedTileSetData& data) const = 0;
    virtual bool ParseImage(ElementT* element, ParsedImage& data) const = 0;
    virtual bool ParseTile(ElementT* element, ParsedTile& data) const = 0;
};

}  // namespace Tile

}  // namespace FA
