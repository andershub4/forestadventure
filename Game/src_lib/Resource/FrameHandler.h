/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "Draw/Animation.h"
#include "Draw/Image.h"

namespace FA {

class SheetManager;

struct AnimationData
{
    std::string sheetId_;
    struct LocationData
    {
        sf::Vector2u start_;
        unsigned int nFrames_;
        unsigned int defaultFrame_ = 0;
    };

    LocationData locationData_;
    bool mirror_;
};

struct ImageData
{
    std::string sheetId_;
    sf::Vector2u position_;
    float rotation_;
};

class FrameHandler
{
public:
    FrameHandler(const SheetManager &sheetManager);
    Animation MakeAnimation(const AnimationData &data) const;
    Image MakeImage(const ImageData &data) const;

private:
    const SheetManager &sheetManager_;
};

}  // namespace FA
