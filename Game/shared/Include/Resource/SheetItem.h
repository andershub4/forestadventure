/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct SheetItem
{
    std::string sheetId_;
    sf::Vector2u position_{};
};

inline bool operator==(const SheetItem& lhs, const SheetItem& rhs)
{
    return std::tie(lhs.sheetId_, lhs.position_) == std::tie(rhs.sheetId_, rhs.position_);
}

inline std::ostream& operator<<(std::ostream& os, const SheetItem& p)
{
    os << OUT2("sheetId", p.sheetId_) << DELIM << OUT2("position", p.position_);

    return os;
}

}  // namespace Shared

}  // namespace FA
