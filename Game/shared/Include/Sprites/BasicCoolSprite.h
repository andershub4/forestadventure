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

namespace Shared {

// Currently, there are no common methods for the sprite classes,
// but I've decided to keep this Basic class in case there will be
// new methods in future, and also keep it as a code reference
// when dealing with multiple sub classes and mocks.
template <class CoolSpriteIfT>
class BasicCoolSprite : public CoolSpriteIfT
{
public:
    virtual void Update(float deltaTime) override {}
    virtual void ApplyTo(Graphic::SpriteIf &sprite) const override {}
};

}  // namespace Shared

}  // namespace FA
