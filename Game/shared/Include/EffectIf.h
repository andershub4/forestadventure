/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Graphic {

class IRenderTarget;

}  // namespace Graphic

namespace Shared {

class EffectIf
{
public:
    virtual ~EffectIf() = default;

    virtual void DrawTo(Graphic::IRenderTarget& renderTarget) const = 0;
    virtual void Update(float deltaTime) = 0;
};

}  // namespace Shared

}  // namespace FA
