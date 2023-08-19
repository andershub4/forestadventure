/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "SfmlPrint.h"

namespace FA {

namespace Shared {

struct AnimationData
{
    std::string sheetId_;
    struct LocationData
    {
        sf::Vector2u start_;
        unsigned int nRects_;
        unsigned int defaultIndex_ = 0;
    };

    LocationData locationData_;
    bool mirror_;
};

inline bool operator==(const AnimationData::LocationData& lhs, const AnimationData::LocationData& rhs)
{
    return std::tie(lhs.start_, lhs.nRects_, lhs.defaultIndex_) == std::tie(rhs.start_, rhs.nRects_, rhs.defaultIndex_);
}

inline std::ostream& operator<<(std::ostream& os, const AnimationData::LocationData& p)
{
    os << OUT2("start", p.start_) << DELIM << OUT2("nRects", p.nRects_) << DELIM
       << OUT2("defaultIndex", p.defaultIndex_);

    return os;
}

inline bool operator==(const AnimationData& lhs, const AnimationData& rhs)
{
    return std::tie(lhs.sheetId_, lhs.locationData_, lhs.mirror_) ==
           std::tie(rhs.sheetId_, rhs.locationData_, rhs.mirror_);
}

inline std::ostream& operator<<(std::ostream& os, const AnimationData& p)
{
    os << OUT2("sheetId", p.sheetId_) << DELIM << OUT2("locationData", p.locationData_) << DELIM
       << OUT2("mirror", p.mirror_);

    return os;
}

}  // namespace Shared

}  // namespace FA
