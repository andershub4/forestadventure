/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AnimationPartIf.h"

namespace FA {

namespace Entity {

template <template <class...> class AnimationPartIfT, class AnimationT, class... Args>
class AnimationPartBase : public AnimationPartIfT<AnimationT, Args...>
{
public:
    AnimationPartBase(std::shared_ptr<AnimationT> animation)
        : animation_(animation)
    {}

    AnimationPartBase() = default;

    virtual void Update(float deltaTime) override { animation_->Update(deltaTime); }

    virtual void ApplyTo(std::shared_ptr<Graphic::DrawableIf> drawable) override { animation_->ApplyTo(drawable); }

protected:
    std::shared_ptr<AnimationT> animation_;
};

}  // namespace Entity

}  // namespace FA
