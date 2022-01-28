/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <string>
#include <tuple>

#include "Draw/Animation.h"

namespace FA {

class SheetManager;

struct AnimationData
{
    std::string key_;
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

class AnimationDb
{
public:
    AnimationDb(const SheetManager &sheetManager);
    void AddAnimation(const AnimationData &data);
    Animation GetAnimation(const std::string &k) const;

private:
    std::map<std::string, Animation> map_;
    const SheetManager &sheetManager_;

private:
    void AddAnimation(const std::string &k, const Animation &animation);
};

}  // namespace FA
