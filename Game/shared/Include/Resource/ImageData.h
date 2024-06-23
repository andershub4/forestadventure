/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SfmlPrint.h"
#include "SheetItem.h"

namespace FA {

namespace Shared {

struct ImageData
{
    ImageData() = default;
    ImageData(const SheetItem& sheetItem)
        : sheetItem_(sheetItem)
    {}

    ImageData(const SheetItem& sheetItem, bool mirror)
        : sheetItem_(sheetItem)
        , mirror_(mirror)
    {}

    SheetItem sheetItem_;
    bool mirror_{false};
};

inline bool operator==(const ImageData& lhs, const ImageData& rhs)
{
    return std::tie(lhs.sheetItem_, lhs.mirror_) == std::tie(rhs.sheetItem_, rhs.mirror_);
}

inline std::ostream& operator<<(std::ostream& os, const ImageData& p)
{
    os << OUT2("sheetItem", p.sheetItem_) << DELIM << OUT2("mirror", p.mirror_);

    return os;
}

}  // namespace Shared

}  // namespace FA
