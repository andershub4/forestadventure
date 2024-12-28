/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AnimationPartIf.h"

#include "Animation/AnimationTraits.h"

namespace FA {

namespace Shared {

template <class T>
class Animation;

}  // namespace Shared

namespace Entity {

template <template <class...> class AnimationPartIfT, class FrameT, class... Args>
class AnimationPartBase : public AnimationPartIfT<FrameT, Args...>
{
protected:
    using DrawableType = typename Shared::AnimationTraits<FrameT>::DrawableT;

public:
    AnimationPartBase(std::shared_ptr<Shared::AnimationIf<FrameT>> animation, DrawableType &drawable)
        : animation_(animation)
        , drawable_(drawable)
    {}

    AnimationPartBase(DrawableType &drawable)
        : drawable_(drawable)
    {}

    virtual void Update(float deltaTime) override
    {
        animation_->Update(deltaTime);
        animation_->ApplyTo(drawable_);
    }

protected:
    std::shared_ptr<Shared::AnimationIf<FrameT>> animation_;
    DrawableType &drawable_;
};

}  // namespace Entity

}  // namespace FA
