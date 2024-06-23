/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct ColliderFrame
{
    sf::Vector2f size_{};
    sf::Vector2f center_{};
};

inline bool operator==(const ColliderFrame& lhs, const ColliderFrame& rhs)
{
    return std::tie(lhs.size_, lhs.center_) == std::tie(rhs.size_, rhs.center_);
}

inline std::ostream& operator<<(std::ostream& os, const ColliderFrame& p)
{
    os << OUT2("size", p.size_) << DELIM << OUT2("center", p.center_);

    return os;
}

}  // namespace Shared

}  // namespace FA
