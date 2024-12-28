/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AnimationPartBase.h"
#include "SingleAnimationPartIf.h"

namespace FA {

namespace Entity {

template <class FrameT>
class SingleAnimationPart : public AnimationPartBase<SingleAnimationPartIf, FrameT>
{
    using AnimationPartBase<SingleAnimationPartIf, FrameT>::DrawableType;

public:
    SingleAnimationPart(std::shared_ptr<Shared::ImageAnimationIf<FrameT>> animation, DrawableType& drawable)
        : AnimationPartBase<SingleAnimationPartIf, FrameT>(animation, drawable)
    {}

    virtual void Enter() override { this->animation_->Restart(); }
};

}  // namespace Entity

}  // namespace FA
