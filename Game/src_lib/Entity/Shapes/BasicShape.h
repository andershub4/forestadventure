/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class BasicShape
{
public:
    virtual void DrawTo(sf::RenderTarget &renderTarget) = 0;
    virtual void SetTransform(const sf::Vector2f &position, float scale) = 0;
};

}  // namespace Entity

}  // namespace FA
