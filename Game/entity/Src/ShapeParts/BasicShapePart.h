/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Graphic {

class SpriteIf;

}  // namespace Graphic

namespace Entity {

class BasicShapePart
{
public:
    virtual ~BasicShapePart() = default;

    virtual void Enter() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void ApplyTo(Graphic::SpriteIf &sprite) const = 0;
    virtual bool IsDrawable() const = 0;
    virtual bool IsCollidable() const = 0;
};

}  // namespace Entity

}  // namespace FA
