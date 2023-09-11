/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class IRenderTarget;

}  // namespace Graphic

namespace Entity {

class BasicShapePart
{
public:
    virtual ~BasicShapePart() = default;

    virtual void Enter() = 0;
    virtual void Update(float deltaTime) = 0;

    virtual void SetPosition(const sf::Vector2f &position) = 0;
    virtual void SetRotation(float rot) = 0;
    virtual void DrawTo(Graphic::IRenderTarget &renderTarget) = 0;
};

}  // namespace Entity

}  // namespace FA
