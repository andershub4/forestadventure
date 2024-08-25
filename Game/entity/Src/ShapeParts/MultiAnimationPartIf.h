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

template <class AnimationT, class KeyT>
class MultiAnimationPartIf : public AnimationPartIf
{
public:
    virtual void Register(const KeyT &key, std::shared_ptr<AnimationT> animation) = 0;
};

}  // namespace Entity

}  // namespace FA
