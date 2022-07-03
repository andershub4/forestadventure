/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <limits>

namespace FA {

namespace Entity {

enum class LayerType : int { Ground = 1, Waterfall = 2 };

inline std::ostream& operator<<(std::ostream& os, const LayerType& e)
{
    std::string str;
    switch (e) {
        case LayerType::Ground:
            str = "Ground";
            break;
        case LayerType::Waterfall:
            str = "Waterfall";
            break;
    }

    os << str;

    return os;
}

}  // namespace Entity

}  // namespace FA
