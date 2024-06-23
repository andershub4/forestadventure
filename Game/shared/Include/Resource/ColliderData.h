/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/Graphics/Rect.hpp>

#include "SfmlPrint.h"
#include "SheetId.h"
#include "SheetItem.h"

namespace FA {

namespace Shared {

struct ColliderData
{
    ColliderData() = default;
    ColliderData(const SheetItem& sheetItem)
        : sheetItem_(sheetItem)
    {}

    ColliderData(const SheetItem& sheetItem, const sf::IntRect& rect)
        : sheetItem_(sheetItem)
        , rect_(rect)
    {}

    ColliderData(const sf::Vector2i& rectSize)
        : sheetItem_({SheetId::Unknown, {0, 0}})
        , rect_{0, 0, rectSize.x, rectSize.y}
    {}

    SheetItem sheetItem_;
    sf::IntRect rect_{};
};

inline bool operator==(const ColliderData& lhs, const ColliderData& rhs)
{
    return std::tie(lhs.sheetItem_, lhs.rect_) == std::tie(rhs.sheetItem_, rhs.rect_);
}

inline std::ostream& operator<<(std::ostream& os, const ColliderData& p)
{
    os << OUT2("sheetItem", p.sheetItem_) << DELIM << OUT2("rect", p.rect_);

    return os;
}

}  // namespace Shared

}  // namespace FA
