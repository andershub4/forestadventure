/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

namespace FA {

class SheetManager;
class Animation;
class Image;

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
