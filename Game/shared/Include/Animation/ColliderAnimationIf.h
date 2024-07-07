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

class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

struct ColliderFrame;

class ColliderAnimationIf
{
public:
    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const = 0;
    virtual bool Intersects(const ColliderAnimationIf &other) const = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool IsCompleted() const = 0;
    virtual void Center() = 0;
    virtual void SetPosition(const sf::Vector2f &position) = 0;
    virtual void SetRotation(float angle) = 0;
};

}  // namespace Shared

}  // namespace FA
