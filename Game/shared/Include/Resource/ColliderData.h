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
#include "SheetId.h"

namespace FA {

namespace Shared {

struct ColliderData
{
    ColliderData() = default;
    ColliderData(const std::string& sheetId, const sf::Vector2u& position)
        : sheetId_(sheetId)
        , position_(position)
    {}

    ColliderData(const std::string& sheetId, const sf::Vector2u& position, const sf::IntRect &rect) 
        : sheetId_(sheetId)
        , position_(position)
        , rect_(rect)
    {}

    ColliderData(const sf::Vector2i& rectSize)
        : sheetId_(SheetId::Unknown)
        , rect_{0, 0, rectSize.x, rectSize.y}
    {}

    std::string sheetId_;
    sf::Vector2u position_{};
    sf::IntRect rect_{};
};

inline bool operator==(const ColliderData& lhs, const ColliderData& rhs)
{
    return std::tie(lhs.sheetId_, lhs.position_, lhs.rect_) ==
           std::tie(rhs.sheetId_, rhs.position_, rhs.rect_);
}

inline std::ostream& operator<<(std::ostream& os, const ColliderData& p)
{
    os << OUT2("sheetId", p.sheetId_) << DELIM << OUT2("position", p.position_) << DELIM
       << OUT2("rect", p.rect_);

    return os;
}

}  // namespace Shared

}  // namespace FA
