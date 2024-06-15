#pragma once
/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RectangleShapeIf;

}  // namespace Graphic

namespace Shared {

class ColliderIf
{
public:
    virtual void Update(float deltaTime) = 0;
    virtual void ApplyTo(Graphic::RectangleShapeIf &rectShape, bool center) const = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool IsCompleted() const = 0;
    virtual void AddRect(const sf::IntRect &rect) = 0;
};

}  // namespace Shared

}  // namespace FA
