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

class CoolSpriteIf
{
public:
    virtual ~CoolSpriteIf() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void SetPosition(const sf::Vector2f& position) = 0;
    virtual void SetRotation(float rot) = 0;
    virtual void DrawTo(Graphic::RenderTargetIf& renderTarget) const = 0;
    virtual void Center() = 0;
};

}  // namespace Shared

}  // namespace FA
