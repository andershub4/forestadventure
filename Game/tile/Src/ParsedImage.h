/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Tile {

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

}  // namespace Tile

}  // namespace FA
