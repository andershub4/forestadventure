/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class ViewIf
{
public:
    virtual ~ViewIf() = default;

    virtual void setSize(const sf::Vector2f &size) = 0;
    virtual void zoom(float factor) = 0;
    virtual void setCenter(const sf::Vector2f &center) = 0;
};

}  // namespace Graphic

}  // namespace FA
