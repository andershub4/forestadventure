/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Graphic {

class SpriteIf;

}  // namespace Graphic

namespace Shared {

struct Frame;

class ImageAnimationIf
{
public:
    virtual void Update(float deltaTime) = 0;
    virtual void ApplyTo(Graphic::SpriteIf &sprite, bool center) const = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool IsCompleted() const = 0;
};

}  // namespace Shared

}  // namespace FA
