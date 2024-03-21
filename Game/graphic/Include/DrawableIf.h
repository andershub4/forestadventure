/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class DrawableIf
{
public:
    virtual ~DrawableIf() = default;

    // sfml has protected draw method, but since it's not public, I don't need it.

private:
    friend class RenderWindow;
    friend class RenderTexture;

private:
    virtual operator const sf::Drawable&() const = 0;
};

}  // namespace Graphic

}  // namespace FA
