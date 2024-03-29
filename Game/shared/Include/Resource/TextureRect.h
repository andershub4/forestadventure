/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <tuple>

#include <SFML/System/Vector2.hpp>

#include "ResourceId.h"
#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct TextureRect
{
    TextureRect() = default;

    TextureRect(ResourceId id, const sf::Vector2i& position, const sf::Vector2i& size)
        : id_(id)
        , position_(position)
        , size_(size)
        , isValid_(true)
    {}

    ResourceId id_{};
    sf::Vector2i position_;
    sf::Vector2i size_;
    bool isValid_{false};
};

inline bool operator==(const TextureRect& lhs, const TextureRect& rhs)
{
    return std::tie(lhs.id_, lhs.position_, lhs.size_, lhs.isValid_) ==
           std::tie(rhs.id_, rhs.position_, rhs.size_, rhs.isValid_);
}

inline std::ostream& operator<<(std::ostream& os, const TextureRect& p)
{
    os << OUT2("id", p.id_) << DELIM << OUT2("position", p.position_) << DELIM << OUT2("size", p.size_) << DELIM
       << OUT2("isValid", p.isValid_);

    return os;
}

}  // namespace Shared

}  // namespace FA
