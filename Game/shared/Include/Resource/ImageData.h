/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct ImageData
{
    ImageData() = default;
    ImageData(const std::string& sheetId, const sf::Vector2u& position)
        : sheetId_(sheetId)
        , position_(position)
    {}

    ImageData(const std::string& sheetId, const sf::Vector2u& position, bool mirror)
        : sheetId_(sheetId)
        , position_(position)
        , mirror_(mirror)
    {}

    std::string sheetId_;
    sf::Vector2u position_;
    bool mirror_{false};
};

inline bool operator==(const ImageData& lhs, const ImageData& rhs)
{
    return std::tie(lhs.sheetId_, lhs.position_, lhs.mirror_) == std::tie(rhs.sheetId_, rhs.position_, rhs.mirror_);
}

inline std::ostream& operator<<(std::ostream& os, const ImageData& p)
{
    os << OUT2("sheetId", p.sheetId_) << DELIM << OUT2("position", p.position_) << DELIM << OUT2("mirror", p.mirror_);

    return os;
}

}  // namespace Shared

}  // namespace FA
