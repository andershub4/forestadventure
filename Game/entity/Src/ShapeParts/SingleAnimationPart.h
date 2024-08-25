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

template <class AnimationT>
class SingleAnimationPart : public AnimationPartBase<SingleAnimationPartIf, AnimationT>
{
public:
    SingleAnimationPart(std::shared_ptr<AnimationT> animation)
        : AnimationPartBase<SingleAnimationPartIf, AnimationT>(animation)
    {}

    virtual void Enter() override { this->animation_->Restart(); }
};

}  // namespace Entity

}  // namespace FA
