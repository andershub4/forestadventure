/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

namespace FA {

class SheetManager;
struct Frame;

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

struct ImageData
{
    std::string sheetId_;
    sf::Vector2u position_;
};

class FrameHandler
{
public:
    std::vector<Frame> MakeFrames(const SheetManager &sheetManager, const AnimationData &data) const;
    Frame MakeFrame(const SheetManager &sheetManager, const ImageData &data) const;
};

}  // namespace FA
