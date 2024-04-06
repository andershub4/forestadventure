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

class CoolSpriteIf
{
public:
    virtual ~CoolSpriteIf() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void ApplyTo(Graphic::SpriteIf &sprite) const = 0;
};

}  // namespace Shared

}  // namespace FA
