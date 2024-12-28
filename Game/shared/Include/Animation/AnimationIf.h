/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>

#include "Animation/AnimationTraits.h"

namespace FA {

namespace Shared {

template <class FrameT>
class AnimationIf
{
protected:
    using DrawableType = typename AnimationTraits<FrameT>::DrawableT;

public:
    virtual ~AnimationIf() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void ApplyTo(DrawableType& drawable) const = 0;
    virtual void RegisterUpdateCB(std::function<void(const AnimationIf<FrameT>&)> updateCB) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Restart() = 0;
    virtual bool IsCompleted() const = 0;
    virtual void Center() = 0;
};

}  // namespace Shared

}  // namespace FA
