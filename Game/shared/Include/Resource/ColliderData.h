/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct ColliderData
{
    ColliderData() = default;
    ColliderData(const std::string sheetId, const sf::Vector2u position)
        : sheetId_(sheetId)
        , position_(position)
    {}

    std::string sheetId_;
    sf::Vector2u position_{};
};

inline bool operator==(const ColliderData& lhs, const ColliderData& rhs)
{
    return std::tie(lhs.sheetId_, lhs.position_) ==
           std::tie(rhs.sheetId_, rhs.position_);
           
}

inline std::ostream& operator<<(std::ostream& os, const ColliderData& p)
{
    os << OUT2("sheetId", p.sheetId_) << DELIM << OUT2("position", p.position_);

    return os;
}

}  // namespace Shared

}  // namespace FA
