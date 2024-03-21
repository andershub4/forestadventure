/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Graphic {

class TextureIf;

}  // namespace Graphic

namespace Shared {

struct Frame
{
    const Graphic::TextureIf* texture_ = nullptr;
    sf::IntRect rect_;
};

inline bool operator==(const Frame& lhs, const Frame& rhs)
{
    return std::tie(lhs.texture_, lhs.rect_) == std::tie(rhs.texture_, rhs.rect_);
}

inline std::ostream& operator<<(std::ostream& os, const Frame& p)
{
    os << OUT2("texture", p.texture_) << DELIM << OUT2("rect", p.rect_);

    return os;
}

}  // namespace Shared

}  // namespace FA
