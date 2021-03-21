/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>

#include "Animation/AnimationFactory.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class TextureManager;
enum class AnimationType;

class AnimationManager
{
public:
    AnimationManager(TextureManager& textureManager);
    ~AnimationManager();

    void RegisterFactories();
    AnimationFactory GetFactory(AnimationType type) const;

private:
    TextureManager& textureManager_;
    std::unordered_map<AnimationType, AnimationFactory> map_;

private:
    void RegisterPlayerFactory();
    void RegisterMoleFactory();
};

}  // namespace FA
