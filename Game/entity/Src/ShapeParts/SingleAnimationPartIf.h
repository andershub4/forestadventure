/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "AnimationPartIf.h"

namespace FA {

namespace Entity {

template <class AnimationT>
class SingleAnimationPartIf : public AnimationPartIf
{
};

}  // namespace Entity

}  // namespace FA
