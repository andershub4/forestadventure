/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Graphic {

class TextureIf;

}  // namespace Graphic

namespace Shared {

struct ImageFrame
{
    const Graphic::TextureIf* texture_ = nullptr;
    sf::IntRect rect_;
    sf::Vector2f center_{};
};

inline bool operator==(const ImageFrame& lhs, const ImageFrame& rhs)
{
    return std::tie(lhs.texture_, lhs.rect_, lhs.center_) == std::tie(rhs.texture_, rhs.rect_, rhs.center_);
}

inline std::ostream& operator<<(std::ostream& os, const ImageFrame& p)
{
    os << OUT2("texture", p.texture_) << DELIM << OUT2("rect", p.rect_) << DELIM << OUT2("center", p.center_);

    return os;
}

}  // namespace Shared

}  // namespace FA
