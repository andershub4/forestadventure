/*
 *	Copyright (C) 2022 Anders Wennmo
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

struct ImageData
{
    ImageData() = default;
    ImageData(const std::string sheetId, const sf::Vector2u position)
        : sheetId_(sheetId)
        , position_(position)
    {}

    ImageData(const std::string sheetId, const sf::Vector2u position, bool mirror)
        : sheetId_(sheetId)
        , position_(position)
        , mirror_(mirror)
    {}

    ImageData(const std::string sheetId, const sf::Vector2u position, const sf::IntRect& rect)
        : sheetId_(sheetId)
        , position_(position)
        , rect_(rect)
    {}

    ImageData(const std::string sheetId, const sf::Vector2u position, bool mirror, const sf::IntRect& rect)
        : sheetId_(sheetId)
        , position_(position)
        , mirror_(mirror)
        , rect_(rect)
    {}

    std::string sheetId_;
    sf::Vector2u position_;
    bool mirror_{false};
    sf::IntRect rect_{0, 0, 0, 0};
};

inline bool operator==(const ImageData& lhs, const ImageData& rhs)
{
    return std::tie(lhs.sheetId_, lhs.position_, lhs.mirror_, lhs.rect_) ==
           std::tie(rhs.sheetId_, rhs.position_, rhs.mirror_, rhs.rect_);
}

inline std::ostream& operator<<(std::ostream& os, const ImageData& p)
{
    os << OUT2("sheetId", p.sheetId_) << DELIM << OUT2("position", p.position_) << DELIM << OUT2("mirror", p.mirror_)
       << DELIM << OUT2("rect", p.rect_);

    return os;
}

}  // namespace Shared

}  // namespace FA
