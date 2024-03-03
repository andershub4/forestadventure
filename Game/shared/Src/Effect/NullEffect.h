/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "EffectIf.h"

namespace FA {

namespace Shared {

class NullEffect : public EffectIf
{
public:
    NullEffect();

    virtual void DrawTo(Graphic::IRenderTarget& renderTarget) const override;
    virtual void Update(float deltaTime) override;
};

}  // namespace Shared

}  // namespace FA
