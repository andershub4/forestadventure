/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct SheetData
{
    std::string name_;
    std::string path_;
    sf::Vector2u rectCount_;
};

inline bool operator==(const SheetData& lhs, const SheetData& rhs)
{
    return std::tie(lhs.name_, lhs.path_, lhs.rectCount_) == std::tie(rhs.name_, rhs.path_, rhs.rectCount_);
}

inline std::ostream& operator<<(std::ostream& os, const SheetData& p)
{
    os << OUT2("name", p.name_) << DELIM << OUT2("path", p.path_) << DELIM << OUT2("rectCount", p.rectCount_);

    return os;
}
}  // namespace Shared

}  // namespace FA
