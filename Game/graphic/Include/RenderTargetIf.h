/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Graphic {

class DrawableIf;

class RenderTargetIf
{
public:
    virtual ~RenderTargetIf() = default;
    // This will do for now, it's simplied, I don't need to deal with RenderStates
    virtual void draw(const DrawableIf &drawable) = 0;
};

}  // namespace Graphic

}  // namespace FA
