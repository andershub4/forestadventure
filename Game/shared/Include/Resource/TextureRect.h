/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "ResourceId.h"
#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct TextureRect
{
    TextureRect() = default;

    TextureRect(ResourceId id, const sf::IntRect& rect)
        : id_(id)
        , rect_(rect)
        , isValid_(true)
    {}

    ResourceId id_{};
    sf::IntRect rect_{};
    bool isValid_{false};
};

inline bool operator==(const TextureRect& lhs, const TextureRect& rhs)
{
    return std::tie(lhs.id_, lhs.rect_, lhs.isValid_) == std::tie(rhs.id_, rhs.rect_, rhs.isValid_);
}

inline std::ostream& operator<<(std::ostream& os, const TextureRect& p)
{
    os << OUT2("id", p.id_) << DELIM << OUT2("rect", p.rect_) << DELIM << OUT2("isValid", p.isValid_);

    return os;
}

}  // namespace Shared

}  // namespace FA
