/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SpriteIf.h"

namespace FA {

namespace Shared {

struct Frame;

class AnimationSpriteIf : public SpriteIf
{
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool IsCompleted() const = 0;
    virtual void AddFrame(const Frame &frame) = 0;
};

}  // namespace Shared

}  // namespace FA
