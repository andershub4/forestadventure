/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "ImageData.h"
#include "Print.h"

namespace FA {

namespace Shared {

using FA::Util::operator<<;

struct TileGraphic
{
    std::vector<ImageData> animation_;
    ImageData image_;
};

inline bool operator==(const TileGraphic& lhs, const TileGraphic& rhs)
{
    return std::tie(lhs.animation_, lhs.image_) == std::tie(rhs.animation_, rhs.image_);
}

inline std::ostream& operator<<(std::ostream& os, const TileGraphic& p)
{
    os << OUT2("animation", p.animation_) << DELIM << OUT2("image", p.image_);

    return os;
}

}  // namespace Shared

}  // namespace FA
