/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

namespace FA {

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

}  // namespace FA
